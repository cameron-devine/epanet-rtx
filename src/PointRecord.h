//
//  PointRecord.h
//  epanet-rtx
//
//  Created by the EPANET-RTX Development Team
//  See README.md and license.txt for more information
//  

#ifndef epanet_rtx_PointRecord_h
#define epanet_rtx_PointRecord_h

// basics
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <map>


#include "Point.h"
#include "Units.h"
#include "rtxMacros.h"
#include "rtxExceptions.h"

using std::string;

namespace RTX {
  
  /*! 
   \class PointRecord
   \brief A Point Record Class for storing and retrieving Points.
   
   The base PointRecord class just keeps short-term records. Derive to add specific persistence implementations
   */
  
  /*! 
   \fn virtual Point PointRecord::point(const std::string &name, time_t time) 
   \brief Get a Point with a specific name at a specific time.
   \param name The name of the data source (tag name).
   \param time The requested time.
   \return The requested Point (as a shared pointer).
   \sa Point
   */
  /*! 
   \fn std::vector<Point> PointRecord::pointsInRange(const std::string &name, time_t startTime, time_t endTime) 
   \brief Get a vector of Points with a specific name within a specific time range.
   \param name The name of the data source (tag name).
   \param startTime The beginning of the requested time range.
   \param endTime The end of the requested time range.
   \return The requested Points (as a vector of shared pointers)
   \sa Point
   */
  
    
  class PointRecord : public RTX_object {
    
  public:
    
    class IdentifierUnitsList {
    public:
      IdentifierUnitsList();
      bool hasIdentifierAndUnits(const std::string& identifier, const Units& units);
      std::pair<bool,bool> doesHaveIdUnits(const std::string& identifier, const Units& units);
      void set(const std::string& identifier, const Units& units);
      std::map< std::string, Units> *get();
      void clear();
      size_t count();
      bool empty();
    private:
      std::shared_ptr< std::map< std::string, Units> > _d;
    };
    
    typedef std::pair<std::string,Units> nameUnitsPair;
    RTX_BASE_PROPS(PointRecord);
    typedef std::pair<time_t, time_t> time_pair_t;
    
    PointRecord();
    virtual ~PointRecord() {};
    
    std::string name();
    void setName(std::string name);
    
    virtual bool registerAndGetIdentifierForSeriesWithUnits(std::string recordName, Units units);    // registering record names.
    virtual IdentifierUnitsList identifiersAndUnits();
    
    bool exists(const std::string& name, const Units& units);
    
    //virtual bool isPointAvailable(const string& identifier, time_t time);
    virtual Point point(const string& identifier, time_t time);
    virtual Point pointBefore(const string& identifier, time_t time);
    virtual Point pointAfter(const string& identifier, time_t time);
    virtual std::vector<Point> pointsInRange(const string& identifier, time_t startTime, time_t endTime);
    virtual void addPoint(const string& identifier, Point point);
    virtual void addPoints(const string& identifier, std::vector<Point> points);
    virtual void reset(); // clear memcache for all ids
    virtual void reset(const string& identifier); // clear memcache for just this id
    virtual void invalidate(const string& identifier) {reset(identifier);}; // alias here, override for database implementations
    virtual Point firstPoint(const string& id);
    virtual Point lastPoint(const string& id);
    virtual time_pair_t range(const string& id);
    
    virtual std::ostream& toStream(std::ostream &stream);
    
    virtual void beginBulkOperation() {};
    virtual void endBulkOperation() {};

  protected:
//    std::string _cachedPointId;
//    Point _cachedPoint;
    bool _inBulkOperation;
    
    std::map<std::string,Point> _singlePointCache;
//    std::map<std::string, std::vector<Point> > _pointVectorCache;
    
  private:
    std::string _name;
  
  };
  
  std::ostream& operator<< (std::ostream &out, PointRecord &pr);

}

#endif
