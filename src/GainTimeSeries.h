//
//  GainTimeSeries.h
//  tsflib
//
//  Created by the EPANET-RTX Development Team
//  See README.md and license.txt for more information
//

#include "TimeSeriesFilterSinglePoint.h"

#ifndef __tsflib__GainTimeSeries__
#define __tsflib__GainTimeSeries__

namespace TSF {
  class GainTimeSeries : public TimeSeriesFilterSinglePoint {
    
  public:
    TSF_BASE_PROPS(GainTimeSeries);
    GainTimeSeries();
    
    double gain();
    void setGain(double gain);
    
    Units gainUnits();
    void setGainUnits(Units u);
    
    // chainable
    GainTimeSeries::_sp gain(double v) {this->setGain(v); return share_me(this);};
    GainTimeSeries::_sp gainUnits(Units u) {this->setGainUnits(u); return share_me(this);};
    
  protected:
    Point filteredWithSourcePoint(Point sourcePoint);
    virtual bool canSetSource(TimeSeries::_sp ts);
    virtual void didSetSource(TimeSeries::_sp ts);
    virtual bool canChangeToUnits(Units units);
    
  private:
    double _gain;
    Units _gainUnits;
    
  };
}

#endif /* defined(__tsflib__GainTimeSeries__) */
