#include "sdl2window.hpp"

bool SDL2Window::CreateContext(const std::vector<GLContextParam>& params) {
  bool createdContext = false;

  std::vector<GLContextParam> sortedParams = params;
  std::stable_sort(sortedParams.begin(), sortedParams.end());

  for(auto param : sortedParams) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, param.major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, param.minor);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, param.depth);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, param.doubleBuffered);

    if(param.core) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }
    if(param.gles) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    }
    
    m_sdlWindow = SDL2WindowHandle("OpenGL Test", 0, 0, param.width, param.height);

    if(m_sdlWindow.IsInvalid()) {
      std::cerr << "SDL2Window failed to create. Error: "
                << SDL_GetError() << std::endl;
    }

    m_sdlContext = SDL2ContextHandle(m_sdlWindow);

    if(m_sdlContext.IsInvalid()) {
      std::cerr << "SDL2Window failed to create a context using context " << param.ToString() << "\n SDL reported: "
                << SDL_GetError() << std::endl;
    }

    createdContext = m_sdlContext.IsValid();

    if(m_sdlContext.IsValid()) {
      m_contextParam = param;
      break;
    }
  }

  //if(m_sdlWindow.IsInvalid() || m_sdlContext.IsInvalid()) {
  //  std::cerr << "SDL2Window failed to create an OpenGL context. Error: "
  //            << SDL_GetError() << std::endl;
  //}

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
    madeCurrent = m_sdlContext.MakeCurrent(m_sdlWindow);

    if(!madeCurrent) {
      std::cout << "Failed to make SDL2 OpenGL context current. Error: "
           << SDL_GetError() << std::endl;
    }
  }

  return madeCurrent;
}

void SDL2Window::Display() {
  m_sdlWindow.Swap();
}

GLContextParam SDL2Window::GetCurrentContextInfo() const {
  GLContextParam info;

  info.SetResolution(m_sdlWindow.GetWidth(), m_sdlWindow.GetHeight());

  return info;
}
