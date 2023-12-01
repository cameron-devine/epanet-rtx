//
//  SquareWaveTimeSeries.h
//  tsflib
//

#ifndef __tsflib__SquareWaveTimeSeries__
#define __tsflib__SquareWaveTimeSeries__

#include "TimeSeriesSynthetic.h"

namespace TSF {
  
  class SquareWaveTimeSeries : public TimeSeriesSynthetic {
    
  public:
    TSF_BASE_PROPS(SquareWaveTimeSeries);
    SquareWaveTimeSeries();
    
    Clock::_sp period();
    time_t duration();
    
    void setPeriod(Clock::_sp period);
    void setDuration(time_t duration);
    
  protected:
    Point syntheticPoint(time_t time);
    
  private:
    time_t _duration;
    Clock::_sp _period;
  };
  
}


#endif /* defined(__tsflib__SquareWaveTimeSeries__) */
