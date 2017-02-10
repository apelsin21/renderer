#include <iostream>

#include "sdl2window.hpp"

using namespace std;

vector<GLContextParam> SDL2Window::GetGLContextParams() const {
  return vector<GLContextParam> {
    GLContextParam(4, 5, true, false),  // 4.5 Core Profile
    GLContextParam(4, 5, false, false), // 4.5
    GLContextParam(4, 4, true, false),  // 4.4 Core Profile
    GLContextParam(4, 4, false, false), // 4.4
    GLContextParam(4, 3, true, false),  // 4.3 Core Profile
    GLContextParam(4, 3, false, false), // 4.3
    GLContextParam(4, 2, true, false),  // 4.2 Core Profile
    GLContextParam(4, 2, false, false), // 4.2
    GLContextParam(4, 1, true, false),  // 4.1 Core Profile
    GLContextParam(4, 1, false, false), // 4.1
    GLContextParam(4, 0, true, false),  // 4.0 Core Profile
    GLContextParam(4, 0, false, false), // 4.0
    GLContextParam(4, 0, false, true),  // 4.0 ES 
    GLContextParam(3, 3, true, false),  // 3.3 Core Profile
    GLContextParam(3, 3, false, false), // 3.3
    GLContextParam(3, 2, true, false),  // 3.2 Core Profile
    GLContextParam(3, 2, false, false), // 3.2
    GLContextParam(3, 1, false, false), // 3.1
    GLContextParam(3, 0, false, false), // 3.0
    GLContextParam(3, 0, false, true),  // 3.0 ES
    GLContextParam(2, 1, false, false), // 2.1
    GLContextParam(2, 1, false, true),  // 2.1 ES
    GLContextParam(2, 0, false, false), // 2.0
    GLContextParam(2, 0, false, true),  // 2.0 ES
    GLContextParam(1, 5, false, false),  // 1.5
    GLContextParam(1, 4, false, false),  // 1.4
    GLContextParam(1, 3, false, false),  // 1.3
    GLContextParam(1, 2, false, false),  // 1.2
    GLContextParam(1, 1, false, false),  // 1.1
  };
};

bool SDL2Window::CreateContext(const vector<GLContextParam>& params,
                               unsigned int width, unsigned int height) {
  bool createdContext = false;

  vector<GLContextParam> sortedParams = params;
  stable_sort(sortedParams.begin(), sortedParams.end());

  for(vector<GLContextParam>::const_iterator it = sortedParams.begin();
    it < sortedParams.end() && !createdContext;
    ++it) {

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, it->majorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, it->minorVersion);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, it->depthSize);

    if(it->isDoubleBuffered) {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    } else {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
    }

    if(it->isCoreProfile) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    } else if(it->isGLES) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    }
    
    m_sdlWindow = SDL_CreateWindow("OpenGL Test",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	width, height, SDL_WINDOW_OPENGL);

    m_sdlContext = SDL_GL_CreateContext(m_sdlWindow);

    if(m_sdlContext) {
      createdContext = true;
      m_contextParam = *it;
    }
  }

  if(!m_sdlWindow || !m_sdlContext) {
      cerr << "SDL2Window failed to create an OpenGL context. Error: "
         << SDL_GetError() << endl;
  }

  return createdContext;
}

bool SDL2Window::Init(unsigned int width, unsigned int height) {
  if(IsInitialized()) {
    return false;
  }

  const vector<GLContextParam>& params = GetGLContextParams();

  //If the return value isn't zero, SDL is initialized.
  bool sdlIsInitialized = SDL_WasInit(SDL_INIT_VIDEO) == 0 ? false : true;

  if(sdlIsInitialized) {
    cout << "SDL2 was already initialized during init.\n";
  } else if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Unable to initialize SDL2. Error: " << SDL_GetError() << endl;
    return false;
  }

  bool createdContext = CreateContext(params, width, height);

  if(createdContext) {
    int err = SDL_GL_MakeCurrent(m_sdlWindow, m_sdlContext);

    if(err == 0) {
      m_isInitialized = true;
    } else {
      cout << "Failed to make SDL2 OpenGL context current. Error: "
           << SDL_GetError() << endl;

      createdContext = false;
    }
  }

  return createdContext;
}
