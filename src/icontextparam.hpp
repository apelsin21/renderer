#ifndef ICONTEXTPARAM_HPP
#define ICONTEXTPARAM_HPP

#include <string>

template<class T>
class IContextParam {
public:
  virtual ~IContextParam() {}

  virtual std::string ToString() const = 0;

  virtual bool operator== (const T& obj) const = 0;
};

#endif
