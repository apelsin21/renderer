#include "glcontextparam.hpp"

using namespace std;

string GLContextParam::ToString() const {
  const string major = to_string(majorVersion), minor = to_string(minorVersion);
  const string version = "OpenGL " + major + "." + minor;
  const string depth = to_string(depthSize) + " depth bits";
  const string core = isCoreProfile ? "core" : "compat";
  const string gles = isGLES ? "ES " : "";
  const string doubleBuffered = isDoubleBuffered ? "double buffered" : "";

  return version
    + " " + gles + core
    + ", " + depth
    + ", " + doubleBuffered;
}

bool GLContextParam::operator== (const GLContextParam& other) const {
  const bool equalMajor = majorVersion == other.majorVersion;
  const bool equalMinor = minorVersion == other.minorVersion;
  const bool equalVersion = equalMajor && equalMinor;
  const bool equalDepthBits = depthSize == other.depthSize;

  const bool equalCore = isCoreProfile == other.isCoreProfile;
  const bool equalGLES = isGLES == other.isGLES;
  const bool equalDoubleBuffered = isDoubleBuffered == other.isDoubleBuffered;

  return equalVersion && equalCore && equalGLES && equalDoubleBuffered && equalDepthBits;
}
bool GLContextParam::operator!= (const GLContextParam& other) const {
  const bool areEqual = this == &other;
  return areEqual == false;
}
bool GLContextParam::operator< (const GLContextParam& other) const {
  if(majorVersion < other.majorVersion) {
    return true;
  } else if(majorVersion == other.majorVersion) {
    if(minorVersion < other.minorVersion) {
      return true;
    } else if(minorVersion > other.minorVersion) {
      return false;
    }
  } else if(majorVersion > other.majorVersion) {
    return false;
  }

  if(isCoreProfile < other.isCoreProfile) {
    return true;
  };

  if(isGLES < other.isGLES) {
    return true;
  }

  return isDoubleBuffered < other.isDoubleBuffered;
}
bool GLContextParam::operator> (const GLContextParam& other) const {
  if(majorVersion > other.majorVersion) {
    return true;
  } else if(majorVersion == other.majorVersion) {
    if(minorVersion > other.minorVersion) {
      return true;
    } else if(minorVersion < other.minorVersion) {
      return false;
    }
  } else if(majorVersion < other.majorVersion) {
    return false;
  }

  if(isCoreProfile > other.isCoreProfile) {
    return true;
  }

  if(isGLES > other.isGLES) {
    return true;
  }

  return isDoubleBuffered > other.isDoubleBuffered;
}
