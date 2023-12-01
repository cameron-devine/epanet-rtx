#include "GainTimeSeries.h"

using namespace TSF;
using namespace std;

GainTimeSeries::GainTimeSeries() {
  _gain = 1.;
  _gainUnits = TSF_DIMENSIONLESS;
}

double GainTimeSeries::gain() {
  return _gain;
}
void GainTimeSeries::setGain(double gain) {
  _gain = gain;
  this->invalidate();
}

Units GainTimeSeries::gainUnits() {
  return _gainUnits;
}
void GainTimeSeries::setGainUnits(TSF::Units u) {
  _gainUnits = u;
  this->invalidate();
  
  // need to alter dimension of my own units in response?
  if (this->source() && !(this->units().isSameDimensionAs(u * this->source()->units()))) {
    this->setUnits(u * this->source()->units());
  }
}


Point GainTimeSeries::filteredWithSourcePoint(TSF::Point sourcePoint) {
  Point p = sourcePoint * gain();
  Point newPoint = Point::convertPoint(p, (this->source()->units() * this->gainUnits()), this->units());
  return newPoint;
}


bool GainTimeSeries::canSetSource(TimeSeries::_sp ts) {
  return true;
}

void GainTimeSeries::didSetSource(TimeSeries::_sp ts) {
  Units derived = ts->units() * this->gainUnits();
  if (!this->units().isSameDimensionAs(derived) || this->units() == TSF_NO_UNITS) {
    this->setUnits(derived);
  }
}

bool GainTimeSeries::canChangeToUnits(Units units) {
  
  if (!this->source()) {
    return true;
  }
  
  if (units.isSameDimensionAs(this->source()->units() * this->gainUnits())) {
    return true;
  }
  
  if ((this->units().isInvalid() || units.isInvalid()) && units.isInvalid()) {
    return true;
  }
  
  return false;
}

