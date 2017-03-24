#include "sdl2window.hpp"

SDL2Window::~SDL2Window() {
  if(m_sdlWindow) {
    SDL_DestroyWindow(m_sdlWindow);
  }

  if(m_sdlContext) {
    SDL_GL_DeleteContext(m_sdlContext);
  }
}

bool SDL2Window::CreateContext(const std::vector<GLContextParam>& params) {
  bool createdContext = false;

  std::vector<GLContextParam> sortedParams = params;
  std::stable_sort(sortedParams.begin(), sortedParams.end());

  for(auto param : sortedParams) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, param.majorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, param.minorVersion);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, param.depthSize);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, param.isDoubleBuffered);

    if(param.isCoreProfile) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }
    if(param.isGLES) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    }
    
    m_sdlWindow = SDL_CreateWindow("OpenGL Test",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	param.width, param.height, SDL_WINDOW_OPENGL);

    m_sdlContext = SDL_GL_CreateContext(m_sdlWindow);

    if(m_sdlContext) {
      createdContext = true;
      m_contextParam = param;
      break;
    }
  }

  if(!m_sdlWindow || !m_sdlContext) {
    std::cerr << "SDL2Window failed to create an OpenGL context. Error: "
         << SDL_GetError() << std::endl;
  }

  return createdContext;
}

bool SDL2Window::Init() {
  return SDL_WasInit(SDL_INIT_VIDEO) ? SDL_Init(SDL_INIT_VIDEO) : true;
}

bool SDL2Window::IsInitialized() const {
  return SDL_WasInit(SDL_INIT_VIDEO);
}

void SDL2Window::Deinit() {
  if(SDL_WasInit(SDL_INIT_VIDEO)) {
    SDL_Quit();
  }
}

bool SDL2Window::MakeCurrent() {
  bool madeCurrent = false;

  if(SDL_WasInit(SDL_INIT_VIDEO)) {
    int err = SDL_GL_MakeCurrent(m_sdlWindow, m_sdlContext);

    if(err == 0) {
      madeCurrent = true;
    } else {
      std::cout << "Failed to make SDL2 OpenGL context current. Error: "
           << SDL_GetError() << std::endl;
    }
  }

  return madeCurrent;
}

void SDL2Window::Display() {
  SDL_GL_SwapWindow(m_sdlWindow);
}
