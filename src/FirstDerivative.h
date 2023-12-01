//
//  FirstDerivative.h
//  tsflib
//
//  Created by the EPANET-RTX Development Team
//  See README.md and license.txt for more information
//  

#ifndef tsflib_FirstDerivative_h
#define tsflib_FirstDerivative_h

#include "TimeSeriesFilter.h"

namespace TSF {
  
  class FirstDerivative : public TimeSeriesFilter {
  public:
    TSF_BASE_PROPS(FirstDerivative);
    FirstDerivative();
    virtual ~FirstDerivative();
    virtual std::ostream& toStream(std::ostream &stream);
    
  protected:
    PointCollection filterPointsInRange(TimeRange range);
    bool canSetSource(TimeSeries::_sp ts);
    void didSetSource(TimeSeries::_sp ts);
    bool canChangeToUnits(Units units);

  };
  
}// namespace

#endif
