//
//  IntegratorTimeSeries.cpp
//  tsflib
//
//  Created by Sam Hatchett on 2/13/15.
//
//

#include "IntegratorTimeSeries.h"


using namespace TSF;
using namespace std;


void IntegratorTimeSeries::setResetClock(Clock::_sp resetClock) {
  _reset = resetClock;
  this->invalidate();
}

Clock::_sp IntegratorTimeSeries::resetClock() {
  return _reset;
}

PointCollection IntegratorTimeSeries::filterPointsInRange(TimeRange range) {

  vector<Point> outPoints;
  Units fromUnits = this->source()->units();
  PointCollection data(vector<Point>(), fromUnits * TSF_SECOND);
  
  if (!this->resetClock()) {
    return PointCollection(vector<Point>(), this->units());
  }
  
  // back up to previous reset clock tick
  time_t lastReset = this->resetClock()->timeBefore(range.start + 1);
  
  // make sure the reset is honored. the time value we have here may
  // be before the actual reset. we will compensate later on.
  time_t leftMostTime = this->source()->timeBefore(lastReset + 1);
  if (leftMostTime == 0) {
    // no data prior to a reset. get the start-time for data availability
    leftMostTime = this->source()->timeAfter(lastReset);
    lastReset = leftMostTime;
  }
  
  // get next point in case it's out of the specified range
  time_t seekRightTime = this->source()->timeAfter(range.end - 1);
  if (seekRightTime > 0) {
    range.end = seekRightTime;
  }
  
  TimeRange sourceQuery(leftMostTime, range.end);
  PointCollection sourceData = this->source()->pointCollection(sourceQuery);
  
  if (sourceData.count() < 2) {
    // special edge-case: one point is returned. implicit re-set?
    if (sourceData.count() == 1) {
      Point p(sourceData.points().front().time, 0);
      p.addQualFlag(Point::tsf_integrated);
      outPoints.push_back(p);
    }
    else {
      return PointCollection(vector<Point>(), this->units());
    }
  }
  
  auto raw = sourceData.raw();
  auto cursor = raw.first;
  auto prev = raw.first;
  auto vEnd = raw.second;
  
  time_t nextReset = lastReset;
  double integratedValue = 0;
  
  ++cursor;
  while (cursor != vEnd) {
    time_t dt = cursor->time - prev->time;
    double meanValue = (cursor->value + prev->value) / 2.;
    double area = meanValue * double(dt);
    integratedValue += area;
    // reset interval
    if (cursor->time >= nextReset) {
      // compute the portion of the integral
      // that is calculated for the time interval post-reset
      double postResetPortion = double(cursor->time - nextReset) / (double)dt;
      integratedValue = area * postResetPortion;
      nextReset = this->resetClock()->timeAfter(cursor->time);
    }
    if (range.contains(cursor->time)) {
      Point p(cursor->time, integratedValue);
      p.addQualFlag(Point::tsf_integrated);
      outPoints.push_back(p);
    }
    ++cursor;
    ++prev;
  }
  
  data.setPoints(outPoints);
  data.convertToUnits(this->units());
  
  if (this->willResample()) {
    set<time_t> timeValues = this->timeValuesInRange(range);
    data.resample(timeValues);
  }
  return data;
}


bool IntegratorTimeSeries::canSetSource(TimeSeries::_sp ts) {
  return (!this->source() || this->units().isSameDimensionAs(ts->units() * TSF_SECOND));
}

void IntegratorTimeSeries::didSetSource(TimeSeries::_sp ts) {
  if (this->units().isDimensionless() || !this->units().isSameDimensionAs(ts->units() * TSF_SECOND)) {
    Units newUnits = ts->units() * TSF_SECOND;
    if (newUnits.isDimensionless()) {
      newUnits = TSF_DIMENSIONLESS;
    }
    this->setUnits(newUnits);
  }
}

bool IntegratorTimeSeries::canChangeToUnits(TSF::Units units) {
  if (!this->source()) {
    return true;
  }
  else if (units.isSameDimensionAs(this->source()->units() * TSF_SECOND)) {
    return true;
  }
  else {
    return false;
  }
}



