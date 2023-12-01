//
//  ThresholdTimeSeries.h
//  tsflib
//
//  Created by the EPANET-RTX Development Team
//  See README.md and license.txt for more information
//

#ifndef __tsflib__ThresholdTimeSeries__
#define __tsflib__ThresholdTimeSeries__

#include <iostream>
#include "TimeSeriesFilterSinglePoint.h"

namespace TSF {
  //!   A Status Class to map the input time series into binary status based on a threshold.
  /*!
   This time series class maps a dimensional input into a dimensionless binary status (0/1),
   by comparing the input to a specified threshold condition. Can be used, for instance, to
   convert the derivative of a pump runtime into a pump on/off status.
   */
  
  class ThresholdTimeSeries : public TimeSeriesFilterSinglePoint {
    
  public:
    typedef enum {
      thresholdModeNormal   = 0,
      thresholdModeAbsolute = 1
    } thresholdMode_t;
    
    TSF_BASE_PROPS(ThresholdTimeSeries);
    ThresholdTimeSeries();
    
    double threshold();
    void setThreshold(double threshold);
    
    double value();
    void setValue(double val);
    
    thresholdMode_t mode();
    void setMode(thresholdMode_t mode);
    
    // chainable
    ThresholdTimeSeries::_sp threshold(double v) {this->setThreshold(v); return share_me(this);};
    ThresholdTimeSeries::_sp value(double v) {this->setValue(v); return share_me(this);};
    ThresholdTimeSeries::_sp mode(thresholdMode_t m) {this->setMode(m); return share_me(this);};
    
  protected:
    Point filteredWithSourcePoint(Point sourcePoint);
    virtual void didSetSource(TimeSeries::_sp ts);
    virtual bool canChangeToUnits(Units units);
    
  private:
//    Point filteredSingle(Point p, Units sourceU);
    double _threshold;
    double _fixedValue;
    thresholdMode_t _mode;
    
  };
}
#endif /* defined(__tsflib__ThresholdTimeSeries__) */
