#include <iostream>

#include "sdl2window.hpp"

std::vector<GLContextParam> SDL2Window::GetGLContextParams() const {
  return std::vector<GLContextParam> {
    GLContextParam(3, 3, true, false),  // 3.3 Core Profile
    GLContextParam(3, 2, true, false),  // 3.2 Core Profile
    GLContextParam(3, 1, false, false), // 3.1
    GLContextParam(3, 0, false, false), // 3.0
    GLContextParam(2, 1, false, false), // 2.1
    GLContextParam(2, 1, false, true),  // 2.1 ES
    GLContextParam(2, 0, false, false), // 2.0
    GLContextParam(2, 0, false, true)   // 2.0 ES
  };
};

bool SDL2Window::CreateContext(const std::vector<GLContextParam>& params) {
  bool createdContext = false;

  for(std::vector<GLContextParam>::const_iterator it = params.begin();
    it < params.end() && !createdContext;
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
    } m_sdlWindow = SDL_CreateWindow("OpenGL Test",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	800, 600, SDL_WINDOW_OPENGL);

    m_sdlContext = SDL_GL_CreateContext(m_sdlWindow);

    if(m_sdlContext) {
      createdContext = true;
      m_contextParam = *it;
    }
  }

  if(!m_sdlWindow || !m_sdlContext) {
      std::cerr << "SDL2Window failed to create an OpenGL context. Error: "
         << SDL_GetError() << std::endl;
  }

  return createdContext;
}

bool SDL2Window::Init() {
  if(IsInitialized()) {
    return false;
  }

  const std::vector<GLContextParam>& params = GetGLContextParams();

  //If the return value isn't zero, SDL is initialized.
  bool sdlIsInitialized = SDL_WasInit(SDL_INIT_VIDEO) == 0 ? false : true;

  if(sdlIsInitialized) {
    std::cout << "SDL2 was already initialized during init.\n";
  } else if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Unable to initialize SDL2. Error: " << SDL_GetError() << std::endl;
    return false;
  }

  bool createdContext = CreateContext(params);

  if(createdContext) {
    int err = SDL_GL_MakeCurrent(m_sdlWindow, m_sdlContext);

    if(err == 0) {
      m_isInitialized = true;
    } else {
      std::cout << "Failed to make SDL2 OpenGL context current. Error: "
           << SDL_GetError() << std::endl;

      createdContext = false;
    }
  }

  return createdContext;
}
