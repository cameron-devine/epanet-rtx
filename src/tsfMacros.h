//
//  tsfMacros.h
//  tsflib
//
//  Created by the EPANET-RTX Development Team
//  See README.md and license.txt for more information
//  

#ifndef tsflib_tsfMacros_h
#define tsflib_tsfMacros_h

#include <iostream>
#include <memory>

#include "TSF_Visitable.h"



#define TSF_BASE_PROPS(type) typedef std::shared_ptr<type> _sp; TSF_VISITABLE(); std::shared_ptr<type> sp() {return share_me(this);}

namespace TSF {
  class TSF_object : public std::enable_shared_from_this<TSF_object>, public TSF_VISITABLE_TYPE {
  public:
    TSF_BASE_PROPS(TSF_object);
    
    template<class T>
    std::shared_ptr<T> share_me(T* thisPtr) {
      return std::static_pointer_cast<T>(shared_from_this());
    }
    
  };
  
  typedef TSF_object::_sp TSF_ptr;
}


#define TSF_MAX_CHAR_STRING 512
#define TSF_MAX(x,y) x>y?x:y
#define TSF_MIN(x,y) x<y?x:y

// silly macros for silly string comparison
#include <boost/algorithm/string/predicate.hpp>
#define TSF_STRINGS_ARE_EQUAL(x,y) (boost::algorithm::iequals(x,y))
#define TSF_STRINGS_ARE_EQUAL_CS(x,y) (x.compare(y)==0)


#ifndef TSF_BUFFER_DEFAULT_CACHESIZE
#define TSF_BUFFER_DEFAULT_CACHESIZE 100
#endif


#ifdef DEBUG
#define DebugLog std::cout
#else
#define DebugLog if(false) std::cout
#endif

#define EOL '\n'


#endif
