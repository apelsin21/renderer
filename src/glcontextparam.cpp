#include "glcontextparam.hpp"

void GLContextParam::set_version(int ma, int mi, bool c, bool g) {
  major = ma;
  minor = mi;
  core = c;
  gles = g;
}
void GLContextParam::set_resolution(int w, int h) {
  width = w;
  height = h;
}

std::string GLContextParam::to_string() const {
  std::ostringstream ss;
  ss << "OpenGL " << major << "." << minor
     << " " << (gles ? "ES " : "") << (core ? "core" : "compat")
     << ", " << depth << " depth bits"
     << ", " << (doubleBuffered ? "double buffered" : "")
     << ", " << width << "x" << height;

  return ss.str();
}

bool GLContextParam::operator== (const GLContextParam& other) const {
  return
    major == other.major &&
    minor == other.minor && 
    depth == other.depth &&
    width == other.width && 
    height == other.height &&
    core == other.core && 
    gles == other.gles && 
    doubleBuffered == other.doubleBuffered;
}
bool GLContextParam::operator!= (const GLContextParam& other) const {
  return !operator==(other);
}
bool GLContextParam::operator< (const GLContextParam& other) const {
  if(major < other.major) {
    return true;
  } else if(major == other.major) {
    if(minor < other.minor) {
      return true;
    } else if(minor > other.minor) {
      return false;
    }
  } else if(major > other.major) {
    return false;
  }

  if(core < other.core) {
    return true;
  };

  if(gles < other.gles) {
    return true;
  }

  return doubleBuffered < other.doubleBuffered;
}
bool GLContextParam::operator> (const GLContextParam& other) const {
  if(major > other.major) {
    return true;
  } else if(major == other.major) {
    if(minor > other.minor) {
      return true;
    } else if(minor < other.minor) {
      return false;
    }
  } else if(major < other.major) {
    return false;
  }

  if(core > other.core) {
    return true;
  }

  if(gles > other.gles) {
    return true;
  }

  return doubleBuffered > other.doubleBuffered;
}
