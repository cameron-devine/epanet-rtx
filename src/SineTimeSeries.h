//
//  SineTimeSeries.h
//  tsflib
//
//  Created by the EPANET-RTX Development Team
//  See README.md and license.txt for more information
//

#ifndef __tsflib__SineTimeSeries__
#define __tsflib__SineTimeSeries__

#include "TimeSeriesSynthetic.h"

namespace TSF {
  
  class SineTimeSeries : public TimeSeriesSynthetic {
    
  public:
    TSF_BASE_PROPS(SineTimeSeries);
    SineTimeSeries(double magnitude = 1., time_t period = 86400);
    
    time_t period();
    double magnitude();
    
    void setPeriod(time_t p) {_period = p;};
    void setMagnitude(double m) {_magnitude = m;};
    
  protected:
    Point syntheticPoint(time_t time);
    
  private:
    time_t _period;
    double _magnitude;
  };
  
}


#endif /* defined(__tsflib__SineTimeSeries__) */
