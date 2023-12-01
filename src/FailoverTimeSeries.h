//
//  FailoverTimeSeries.h
//  tsflib
//
//  Open Water Analytics [wateranalytics.org]
//  See README.md and license.txt for more information
//

#ifndef __tsflib__FailoverTimeSeries__
#define __tsflib__FailoverTimeSeries__

#include "TimeSeriesFilterSecondary.h"

#include <iostream>


namespace TSF {
  class FailoverTimeSeries : public TimeSeriesFilterSecondary
  {
  public:
    TSF_BASE_PROPS(FailoverTimeSeries);
    
    time_t maximumStaleness();
    void setMaximumStaleness(time_t stale);
    
    void swapSourceWithFailover();
    
    time_t timeBefore(time_t time);
    time_t timeAfter(time_t time);

    FailoverTimeSeries::_sp staleness(time_t seconds) {this->setMaximumStaleness(seconds); return share_me(this);};
    
  protected:
    bool canSetSecondary(TimeSeries::_sp secondary);
    PointCollection filterPointsInRange(TimeRange range);
    std::set<time_t> timeValuesInRange(TimeRange range);
    bool canSetSource(TimeSeries::_sp ts);
    
  private:
    time_t _stale;
  };
}








#endif /* defined(__tsflib__FailoverTimeSeries__) */
