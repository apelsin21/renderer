#ifndef GLCONTEXTPARAM_HPP
#define GLCONTEXTPARAM_HPP

#include <sstream>

#include "icontextparam.hpp"

class GLContextParam : public IContextParam<GLContextParam> {
public:
  int major = 3, minor = 0, depth = 24, width = 800, height = 600;
  bool core = true, gles = false, doubleBuffered = true;

  GLContextParam() {}
  ~GLContextParam() {}

  GLContextParam(int ma, int mi, bool c, bool g) :
    major(ma), minor(mi), core(c), gles(g) {}

  bool SupportsModernGL() const;

  void SetVersion(int ma, int mi, bool c, bool g);
  void SetResolution(int w, int h);

  bool operator== (const GLContextParam& other) const;
  bool operator!= (const GLContextParam& other) const;
  bool operator< (const GLContextParam& other) const;
  bool operator> (const GLContextParam& other) const;

  std::string ToString() const;
};

#endif
