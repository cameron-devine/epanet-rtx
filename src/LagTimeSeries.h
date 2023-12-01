//
//  LagTimeSeries.h
//  tsflib
//
//  Created by Sam Hatchett on 1/20/15.
//
//

#ifndef __tsflib__LagTimeSeries__
#define __tsflib__LagTimeSeries__

#include <stdio.h>

#include "TimeSeriesFilter.h"

namespace TSF {
  class LagTimeSeries : public TimeSeriesFilter {
  public:
    TSF_BASE_PROPS(LagTimeSeries);
    LagTimeSeries();
    
    void setOffset(time_t offset);
    time_t offset();
    
    time_t timeAfter(time_t t);
    time_t timeBefore(time_t t);
    
    // chainable
    LagTimeSeries::_sp lag(time_t seconds) {this->setOffset(seconds); return share_me(this);};
    
  protected:
    bool willResample();
    PointCollection filterPointsInRange(TimeRange range);
    std::set<time_t> timeValuesInRange(TimeRange range);
    
  private:
    time_t _lag;
    
  };
}

#endif /* defined(__tsflib__LagTimeSeries__) */
