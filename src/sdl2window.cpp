#include "sdl2window.hpp"

bool SDL2Window::CreateContext(const GLContextParam& param) {
  bool createdContext = false;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, param.major);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, param.minor);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,            param.depth);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,          param.doubleBuffered);

  if(param.core) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  }
  if(param.gles) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  }
  
  SDL2WindowHandle window("OpenGL Test", -1, -1, param.width, param.height);

  if(window.IsValid()) {
		SDL2ContextHandle context(window);

		if(context.IsValid()) {
			createdContext = true;
			m_contextHandle = context;
			m_windowHandle = std::move(window);
			m_contextParam = param;
		} else {
			std::cerr << "SDL2Window failed to create an OpenGL context. Error: "
								<< SDL_GetError() << std::endl;
			createdContext = false;
		}
  } else {
    std::cerr << "SDL2Window failed to create an SDL Window. Error:\n"
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
    madeCurrent = m_contextHandle.MakeCurrent(m_windowHandle);

    if(!madeCurrent) {
      std::cerr << "Failed to make SDL2 OpenGL context current. Error: "
           << SDL_GetError() << std::endl;
    }
  }

  return madeCurrent;
}

void SDL2Window::Display() {
  m_windowHandle.Swap();
}

GLContextParam SDL2Window::GetCurrentContextInfo() const {
  GLContextParam info = m_contextParam;
  info.SetResolution(m_windowHandle.GetWidth(), m_windowHandle.GetHeight());
  return info;
}
