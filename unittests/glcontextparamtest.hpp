#ifndef GLCONTEXTPARAMTEST_HPP
#define GLCONTEXTPARAMTEST_HPP

#include "catch.hpp"
#include "glcontextparam.hpp"

std::vector<GLContextParam> GetUnsortedContextVector() {
  return std::vector<GLContextParam> {
    GLContextParam(1, 3, 800, 600, false, false),  // 1.3
    GLContextParam(4, 5, 800, 600, true, false),  // 4.5 Core Profile
    GLContextParam(4, 4, 800, 600, false, false), // 4.4
    GLContextParam(4, 4, 800, 600, true, false),  // 4.4 Core Profile
    GLContextParam(4, 3, 800, 600, false, false), // 4.3
    GLContextParam(3, 2, 800, 600, true, false),  // 3.2 Core Profile
    GLContextParam(3, 2, 800, 600, false, false), // 3.2
    GLContextParam(1, 2, 800, 600, false, false),  // 1.2
    GLContextParam(1, 1, 800, 600, false, false),  // 1.1
    GLContextParam(4, 5, 800, 600, false, false), // 4.5
    GLContextParam(4, 3, 800, 600, true, false),  // 4.3 Core Profile
    GLContextParam(4, 2, 800, 600, false, false), // 4.2
    GLContextParam(4, 1, 800, 600, false, false), // 4.1
    GLContextParam(4, 0, 800, 600, true, false),  // 4.0 Core Profile
    GLContextParam(4, 1, 800, 600, true, false),  // 4.1 Core Profile
    GLContextParam(4, 2, 800, 600, true, false),  // 4.2 Core Profile
    GLContextParam(4, 0, 800, 600, false, false), // 4.0
    GLContextParam(4, 0, 800, 600, false, true),  // 4.0 ES 
    GLContextParam(2, 0, 800, 600, false, false), // 2.0
    GLContextParam(2, 0, 800, 600, false, true),  // 2.0 ES
    GLContextParam(3, 3, 800, 600, true, false),  // 3.3 Core Profile
    GLContextParam(3, 3, 800, 600, false, false), // 3.3
    GLContextParam(3, 1, 800, 600, false, false), // 3.1
    GLContextParam(3, 0, 800, 600, false, false), // 3.0
    GLContextParam(3, 0, 800, 600, false, true),  // 3.0 ES
    GLContextParam(2, 1, 800, 600, false, false), // 2.1
    GLContextParam(2, 1, 800, 600, false, true),  // 2.1 ES
    GLContextParam(1, 5, 800, 600, false, false),  // 1.5
    GLContextParam(1, 4, 800, 600, false, false),  // 1.4
  };
}

std::vector<GLContextParam> GetSortedContextVector() {
  return std::vector<GLContextParam> {
    GLContextParam(1, 1, 800, 600, false, false),  // 1.1 ES 
    GLContextParam(1, 2, 800, 600, false, false),  // 1.2 ES
    GLContextParam(1, 3, 800, 600, false, false),  // 1.3 ES
    GLContextParam(1, 4, 800, 600, false, false),  // 1.4 ES
    GLContextParam(1, 5, 800, 600, false, false),  // 1.5 ES
    GLContextParam(2, 0, 800, 600, false, false), // 2.0
    GLContextParam(2, 0, 800, 600, false, true),  // 2.0 ES
    GLContextParam(2, 1, 800, 600, false, false), // 2.1
    GLContextParam(2, 1, 800, 600, false, true),  // 2.1 ES
    GLContextParam(3, 0, 800, 600, false, false), // 3.0
    GLContextParam(3, 0, 800, 600, false, true),  // 3.0 ES
    GLContextParam(3, 1, 800, 600, false, false), // 3.1
    GLContextParam(3, 2, 800, 600, false, false), // 3.2
    GLContextParam(3, 2, 800, 600, true, false),  // 3.2 Core Profile
    GLContextParam(3, 3, 800, 600, false, false), // 3.3
    GLContextParam(3, 3, 800, 600, true, false),  // 3.3 Core Profile
    GLContextParam(4, 0, 800, 600, false, false), // 4.0
    GLContextParam(4, 0, 800, 600, false, true),  // 4.0 ES 
    GLContextParam(4, 0, 800, 600, true, false),  // 4.0 Core Profile
    GLContextParam(4, 1, 800, 600, false, false), // 4.1
    GLContextParam(4, 1, 800, 600, true, false),  // 4.1 Core Profile
    GLContextParam(4, 2, 800, 600, false, false), // 4.2
    GLContextParam(4, 2, 800, 600, true, false),  // 4.2 Core Profile
    GLContextParam(4, 3, 800, 600, false, false), // 4.3
    GLContextParam(4, 3, 800, 600, true, false),  // 4.3 Core Profile
    GLContextParam(4, 4, 800, 600, false, false), // 4.4
    GLContextParam(4, 4, 800, 600, true, false),  // 4.4 Core Profile
    GLContextParam(4, 5, 800, 600, false, false), // 4.5
    GLContextParam(4, 5, 800, 600, true, false),  // 4.5 Core Profile
  };
}

#endif
