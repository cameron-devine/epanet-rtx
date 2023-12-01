//
//  InversionTimeSeries.h
//  tsflib
//
//  Open Water Analytics [wateranalytics.org]
//  See README.md and license.txt for more information
//

#ifndef __tsflib__InversionTimeSeries__
#define __tsflib__InversionTimeSeries__

#include <iostream>
#include "TimeSeriesFilterSinglePoint.h"

namespace TSF {
  class InversionTimeSeries : public TimeSeriesFilterSinglePoint {
    
  public:
    TSF_BASE_PROPS(InversionTimeSeries);
    
  protected:
    Point filteredWithSourcePoint(Point sourcePoint);
    virtual bool canSetSource(TimeSeries::_sp ts);
    virtual void didSetSource(TimeSeries::_sp ts);
    virtual bool canChangeToUnits(Units units);
    
    
  };
}



#endif /* defined(__tsflib__InversionTimeSeries__) */
