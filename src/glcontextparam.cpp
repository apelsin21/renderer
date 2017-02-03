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
  const bool lessMajor = majorVersion < other.majorVersion;

  //If the major version was greater, the minor version was also greater.
  //If the major versions were equal, the minor versions are compared.
  //If the major version was less, the minor version was also less.
  //
  //So minor version can only be true if the major versions are equal, and
  //the minor version was greater during comparison.
  
  bool lessMinor = lessMajor;

  if(majorVersion == other.majorVersion) {
    lessMinor = minorVersion > other.minorVersion;
  }

  const bool lessVersion = lessMajor && lessMinor;
  const bool lessDepthBits = depthSize < other.depthSize;

  //Boolean values in C/C++ are promoted to integers during comparison.
  const bool lessCore = isCoreProfile < other.isCoreProfile;
  const bool lessGLES = isGLES < other.isGLES;
  const bool lessDoubleBuffered = isDoubleBuffered < other.isDoubleBuffered;

  return lessVersion && lessCore && lessGLES && lessDoubleBuffered && lessDepthBits;
}
bool GLContextParam::operator> (const GLContextParam& other) const {
  const int propertyCount = 5;
  int equalCount = 0;
  int greaterCount = 0;

  if(majorVersion > other.majorVersion) {
    greaterCount++;
  } else if(majorVersion == other.majorVersion) {
    const bool isMinorGreater = minorVersion > other.minorVersion;
    const bool isMinorEqual = minorVersion == other.minorVersion;

    if(isMinorGreater) {
      greaterCount++;
    } else if(isMinorEqual) {
      equalCount++;
    }
  }

  if(depthSize > other.depthSize) {
      greaterCount++;
  } else if(depthSize == other.depthSize) {
      equalCount++;
  }

  if(isCoreProfile > other.isCoreProfile) {
      greaterCount++;
  } else if(isCoreProfile == other.isCoreProfile) {
      equalCount++;
  }

  if(isGLES > other.isGLES) {
    greaterCount++;
  } else if(isGLES == other.isGLES) {
    equalCount++;
  }

  if(isDoubleBuffered > other.isDoubleBuffered) {
    greaterCount++;
  } if(isDoubleBuffered == other.isDoubleBuffered) {
    equalCount++;
  }

  //The minimum requirement for this to be greater is for there to be one greater
  //property, the rest need to be atleast equal to the other object.
  bool isGreater = false;
  const bool allFieldsWasAtleastEqual = (equalCount + greaterCount) == propertyCount;

  if(allFieldsWasAtleastEqual && greaterCount > 0) {
    isGreater = true;
  }

  return false;
}
