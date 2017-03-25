#ifndef ICONTEXTPARAM_HPP
#define ICONTEXTPARAM_HPP

#include <string>

template<typename T>
class IContextParam {
public:
  virtual inline bool operator== (const T& other) const = 0;
  virtual inline bool operator!= (const T& other) const = 0;
  virtual inline bool operator<  (const T& other) const = 0;
  virtual inline bool operator>  (const T& other) const = 0;
};

#endif
