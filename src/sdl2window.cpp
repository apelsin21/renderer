#include "sdl2window.hpp"

bool SDL2Window::initialize(const GLContextParam& param)
{
  bool initializedSuccessfully = false;

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
		SDL_CreateWindow(param.title.c_str(), 0, 0, param.width, param.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)
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

void SDL2Window::consume_events(std::function<void()> on_exit,
                                std::function<void(int width, int height)> on_resize,
                                std::function<void(int x, int y)> on_move,
                                std::function<void()> on_maximize,
                                std::function<void()> on_minimize,
                                std::function<void()> on_show,
                                std::function<void()> on_hide,
                                std::function<void()> on_expose,
                                std::function<void()> on_mouse_enter,
                                std::function<void()> on_mouse_leave,
                                std::function<void()> on_focus,
                                std::function<void()> on_blur,
                                std::function<void()> on_restore) {
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_WINDOWEVENT) {
      switch(event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
          on_exit();
          break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
          on_resize(event.window.data1, event.window.data2);
          break;
        case SDL_WINDOWEVENT_MOVED:
          on_move(event.window.data1, event.window.data2);
          break;
        case SDL_WINDOWEVENT_MINIMIZED:
          on_minimize();
          break;
        case SDL_WINDOWEVENT_MAXIMIZED:
          on_maximize();
          break;
        case SDL_WINDOWEVENT_RESTORED:
          on_restore();
          break;
        case SDL_WINDOWEVENT_ENTER:
          on_mouse_enter();
          break;
        case SDL_WINDOWEVENT_LEAVE:
          on_mouse_leave();
          break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
          on_focus();
          break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
          on_blur();
          break;
        default:
          break;
      }
    }
  }
}
