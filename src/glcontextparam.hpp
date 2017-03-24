#ifndef GLCONTEXTPARAM_HPP
#define GLCONTEXTPARAM_HPP

#include <sstream>

#include "icontextparam.hpp"

class GLContextParam : public IContextParam<GLContextParam> {
public:
  int majorVersion, minorVersion, depthSize, width, height;
  bool isCoreProfile, isGLES, isDoubleBuffered;

  GLContextParam(int ma, int mi, int depth, int w, int h,
                 bool core, bool gles, bool doubleBuffered) :
      majorVersion(ma), minorVersion(mi), depthSize(depth),
      isCoreProfile(core), isGLES(gles), isDoubleBuffered(doubleBuffered) {}

  GLContextParam(int ma, int mi, int w, int h, bool core, bool gles) :
      majorVersion(ma), minorVersion(mi), width(w), height(h),
      depthSize(24), isCoreProfile(core), isGLES(gles), isDoubleBuffered(true) {}

  GLContextParam() : majorVersion(0), minorVersion(0),
    depthSize(0), width(0), height(0),
    isCoreProfile(false), isGLES(false), isDoubleBuffered(false) {}

  ~GLContextParam() {
  }

  bool SupportsModernGL() const;

  bool operator== (const GLContextParam& other) const;
  bool operator!= (const GLContextParam& other) const;
  bool operator< (const GLContextParam& other) const;
  bool operator> (const GLContextParam& other) const;

  std::string ToString() const;
};

#endif
