#include <iostream>
#include <vector>

#include <epoxy/gl.h>

#include "sdl2window.hpp"

using namespace std;

int main(void) {
  SDL2Window window;

  if(window.Init()) {
    const GLContextParam& param = window.GetContextParam();
    const string paramString = param.ToString();

    cout << paramString << endl;
    cout << "Epoxy OpenGL version: " << epoxy_gl_version() << endl;
    cout << "GL_VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << endl;
  } else {
    cout << "Failed to intialize SDL2 window.\n";
    return 1;
  }

  return 0;
}
