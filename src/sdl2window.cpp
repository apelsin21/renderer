#include "sdl2window.hpp"

bool SDL2Window::initialize(const GLContextParam& param)
{
  bool initializedSuccessfully = false;

	std::cout << "initializing window: " << param.ToString() << std::endl;

  SDL_Init(SDL_INIT_VIDEO);

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

  m_sdlWindowHandle = sdl2::window_ptr(
		SDL_CreateWindow("", 0, 0, param.width, param.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)
	);

	if(m_sdlWindowHandle) {
		initializedSuccessfully = m_sdlContextHandle.initialize(m_sdlWindowHandle);
	} else {
		std::cerr << "SDL2 failed to create window: " << SDL_GetError() << std::endl;
	}

	m_initialized = initializedSuccessfully;
  return initializedSuccessfully;
}

void SDL2Window::deinitialize() {
	if(m_initialized) {
		m_sdlContextHandle.deinitialize();

		if(m_sdlWindowHandle) {
			m_sdlWindowHandle.reset();
		}

		if(SDL_WasInit(SDL_INIT_VIDEO)) {
			SDL_Quit();
		}

		m_initialized = false;
	}
}

void SDL2Window::Display() {
	m_sdlContextHandle.Swap(m_sdlWindowHandle);
}
