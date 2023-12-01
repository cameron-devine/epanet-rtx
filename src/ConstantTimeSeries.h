//
//  ConstantTimeSeries.h
//  tsflib
//
//  Created by the EPANET-RTX Development Team
//  See README.md and license.txt for more information
//

#ifndef __tsflib__ConstantTimeSeries__
#define __tsflib__ConstantTimeSeries__

#include "TimeSeriesSynthetic.h"

namespace TSF {
  
  class ConstantTimeSeries : public TimeSeriesSynthetic {
  public:
    TSF_BASE_PROPS(ConstantTimeSeries);
    ConstantTimeSeries();
    
    void setValue(double value);
    double value();
    
  protected:
    Point syntheticPoint(time_t time);
    
  private:
    double _value;
  };
  
}




#endif /* defined(__tsflib__ConstantTimeSeries__) */
