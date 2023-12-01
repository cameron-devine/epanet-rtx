//
//  tsfExceptions.h
//  tsflib
//
//  Created by the EPANET-RTX Development Team
//  See README.md and license.txt for more information
//  

#ifndef tsflib_tsfExceptions_h
#define tsflib_tsfExceptions_h

#include <stdexcept>

namespace TSF {
  
  class TsfException : public std::exception {
  public:
    TsfException(std::string ss = "Unknown") : s(ss) {}
    virtual const char* what() const throw()
    { return s.c_str(); }
    virtual ~TsfException() throw() {}
    std::string s;
  };
  
  class TsfIoException : public TsfException {
  public:
    virtual const char* what() const throw()
    { return "I/O Exception\n"; }
  };
  
  class TsfMethodNotValid : public TsfException {
  public:
    virtual const char* what() const throw()
    { return "Method not Valid\n"; }
  };
  
  class IncompatibleComponent : public TsfException {
    virtual const char* what() const throw()
    { return "Component not compatible\n"; }
  };
}


#endif
