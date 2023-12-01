//
//  OffsetTimeSeries.h
//  tsflib
//
//  Open Water Analytics [wateranalytics.org]
//  See README.md and license.txt for more information
//

#ifndef __tsflib__OffsetTimeSeries__
#define __tsflib__OffsetTimeSeries__

#include <iostream>
#include "TimeSeriesFilterSinglePoint.h"

namespace TSF {
  class OffsetTimeSeries : public TimeSeriesFilterSinglePoint {
  
  public:
    TSF_BASE_PROPS(OffsetTimeSeries);
    OffsetTimeSeries();
    void setOffset(double offset);
    double offset();
    
    // chainable
    OffsetTimeSeries::_sp offset(double v) {this->setOffset(v); return share_me(this);};
    
  protected:
    Point filteredWithSourcePoint(Point sourcePoint);
  private:
    double _offset;
  };
}
#endif /* defined(__tsflib__OffsetTimeSeries__) */
