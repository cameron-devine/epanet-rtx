//
//  MetaTimeSeries.h
//  tsflib
//
//  Created by Sam Hatchett on 4/14/15.
//
//

#ifndef __tsflib__MetaTimeSeries__
#define __tsflib__MetaTimeSeries__

#include <stdio.h>

#include <iostream>
#include "TimeSeriesFilter.h"


namespace TSF {
  //!   A Class to map the input time series into a series whos values are the time gaps between successive points
  
  class MetaTimeSeries : public TimeSeriesFilter {
    
  public:
    TSF_BASE_PROPS(MetaTimeSeries);
    MetaTimeSeries();
    
    enum MetaMode : unsigned int {
      MetaModeGap        =  0,
      MetaModeConfidence =  1,
      MetaModeQuality    =  2
    };
    
    
    MetaMode metaMode();
    void setMetaMode(MetaMode mode);
    
    MetaTimeSeries::_sp mode(MetaMode m) {this->setMetaMode(m); return share_me(this);};
    
  protected:
    PointCollection filterPointsInRange(TimeRange range);
    bool canSetSource(TimeSeries::_sp ts);
    void didSetSource(TimeSeries::_sp ts);
    bool canChangeToUnits(Units units);
    
  private:
    MetaMode _metaMode;
  };
}

#endif /* defined(__tsflib__MetaTimeSeries__) */
