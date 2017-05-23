#ifndef GLCONTEXTPARAM_HPP
#define GLCONTEXTPARAM_HPP

#include <sstream>

//URGH, some gnu compiler versions define a major() and minor() macro,
//and thus polluting our namespace...
#undef major
#undef minor

#include "icontextparam.hpp"

class GLContextParam : public IContextParam<GLContextParam> {
public:
  std::string title;
  int major = 3, minor = 0, depth = 24, width = 800, height = 600;
  bool core = true, gles = false, doubleBuffered = true;

  GLContextParam() {}
  ~GLContextParam() {}

  GLContextParam(const std::string& new_title, int ma, int mi, bool c, bool g) :
    title(new_title), major(ma), minor(mi), core(c), gles(g) {}

  void set_version(int ma, int mi, bool c, bool g);
  void set_resolution(int w, int h);

  bool operator== (const GLContextParam& other) const;
  bool operator!= (const GLContextParam& other) const;
  bool operator<  (const GLContextParam& other) const;
  bool operator>  (const GLContextParam& other) const;

  std::string to_string() const;
};

#endif
