#ifndef TSF_Visitable_hpp
#define TSF_Visitable_hpp

namespace TSF {
  class BaseVisitor {
  public:
    virtual ~BaseVisitor() {};
  };
  
  template <class T>
  class Visitor {
  public:
    virtual void visit(T&) = 0;
  };
  
  class BaseVisitable {
  public:
    virtual ~BaseVisitable() {};
    virtual void accept(BaseVisitor & ) { }
  protected:
    template <class T>
    static void acceptVisitor(T &visited, BaseVisitor &visitor) {
      if (Visitor<T> *p = dynamic_cast< Visitor<T> *> (&visitor)) {
        return p->visit(visited);
      }
      else {
        std::cerr << "Visitor not configured to visit this object" << std::endl;
      }
    }
  };
}

#define TSF_VISITABLE() virtual void accept(TSF::BaseVisitor &v) { return acceptVisitor(*this, v); }
#define TSF_VISITABLE_TYPE TSF::BaseVisitable

#endif /* TSF_Visitable_hpp */
