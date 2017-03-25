#ifndef ICONTEXTPARAM_HPP
#define ICONTEXTPARAM_HPP

#include <string>

template<class T>
class IContextParam {
public:
  virtual bool operator== (const T& other) const = 0;
  virtual bool operator!= (const T& other) const = 0;
  virtual bool operator< (const T& other) const = 0;
  virtual bool operator> (const T& other) const = 0;
};

#endif
