#ifndef SDL2WINDOW_HPP
#define SDL2WINDOW_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "glcontextparam.hpp"
#include "iwindow.hpp"

template<typename Creator, typename Destructor, typename... Arguments>
auto MakeResource(Creator c, Destructor d, Arguments&&... args) {
    auto r = c(std::forward<Arguments>(args)...);
    if (!r) { throw std::system_error(errno, std::generic_category()); }
    return std::unique_ptr<std::decay_t<decltype(*r)>, decltype(d)>(r, d);
}

namespace sdl2 {
	using WindowHandlePtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

	inline WindowHandlePtr MakeWindow(const GLContextParam& param) {
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

		return MakeResource(SDL_CreateWindow, SDL_DestroyWindow,
			"", 0, 0, param.width, param.height, SDL_WINDOW_OPENGL);
	}

	class ContextHandle {
	protected:
			SDL_GLContext m_context;

	public:
		ContextHandle(sdl2::WindowHandlePtr& window) {
			m_context = SDL_GL_CreateContext(window.get());

			if(SDL_GL_MakeCurrent(window.get(), m_context) != 0) {
				std::cout << "make current failed: " << SDL_GetError() << std::endl;
			}
		}
		~ContextHandle() {
			SDL_GL_DeleteContext(m_context);
		}

		void Swap(sdl2::WindowHandlePtr& window) {
			SDL_GL_SwapWindow(window.get());
		}
	};
}

class SDL2Window : public IWindow {
protected:
  sdl2::WindowHandlePtr m_sdlWindowHandle;
  sdl2::ContextHandle m_sdlContextHandle;
  GLContextParam m_contextParam;
public:
  SDL2Window(const GLContextParam& param)
		: m_sdlWindowHandle(sdl2::MakeWindow(param)),
			m_sdlContextHandle(m_sdlWindowHandle) {
  
		m_contextParam = param;
	}
  ~SDL2Window() {
		SDL_Quit();
  }

  GLContextParam GetContextParam() const {
    return m_contextParam;
  }

  void Display();
};

#endif
