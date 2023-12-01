//
//  TimeSeriesFilterSinglePoint.h
//  tsflib
//
//  Created by Sam Hatchett on 1/16/15.
//
//

#ifndef __tsflib__TimeSeriesFilterSinglePoint__
#define __tsflib__TimeSeriesFilterSinglePoint__

#include <stdio.h>
#include "TimeSeriesFilter.h"

namespace TSF {
  class TimeSeriesFilterSinglePoint : public TimeSeriesFilter {
  protected:
    PointCollection filterPointsInRange(TimeRange range); // non-virtual
    virtual Point filteredWithSourcePoint(Point sourcePoint) = 0; // pure virtual. override must convert units.
  };
}

#endif /* defined(__tsflib__TimeSeriesFilterSinglePoint__) */
