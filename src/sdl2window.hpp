#ifndef SDL2WINDOW_HPP
#define SDL2WINDOW_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include "epoxy/gl.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "glcontextparam.hpp"
#include "iwindow.hpp"

namespace sdl2 {
	struct SDLWindowDestroyer {
			void operator()(SDL_Window* w) const {
					SDL_DestroyWindow(w);
			}
	};

	using window_ptr = std::unique_ptr<SDL_Window, SDLWindowDestroyer>;

	class ContextHandle {
	protected:
			SDL_GLContext m_context;
			bool m_initialized = false;
	public:
		ContextHandle() {
		}

		bool initialize(sdl2::window_ptr& window) {
			bool ok = false;
			SDL_GLContext context = SDL_GL_CreateContext(window.get());

			if(context) {
				if(SDL_GL_MakeCurrent(window.get(), context) == 0) {
					ok = true;
					m_context = context;
					m_initialized = true;
				} else {
					std::cerr << "SDL failed to make context current: " << SDL_GetError() << std::endl;
				}
			} else {
				std::cerr << "SDL failed to create context: " << SDL_GetError() << std::endl;
			}

			return ok;
		}
		void deinitialize() {
			if(m_initialized) {
				if(m_context) {
					SDL_GL_DeleteContext(m_context);
				}

				m_initialized = false;
			}
		}

		~ContextHandle() {
			if(m_initialized) {
				SDL_GL_DeleteContext(m_context);
			}
		}

		void Swap(sdl2::window_ptr& window) {
			SDL_GL_SwapWindow(window.get());
		}
	};
}

class IConsumer {
	protected:
	public:
};

class SDL2Window : public IWindow, public IConsumer {
protected:
  sdl2::window_ptr m_sdlWindowHandle;
  sdl2::ContextHandle m_sdlContextHandle;
  GLContextParam m_contextParam;
  bool m_initialized = false;
public:
  SDL2Window() {
	}
  ~SDL2Window() {
    if(m_initialized) {
      SDL_Quit();
    }
  }

	bool is_initialized() const { return m_initialized; }
  bool initialize(const GLContextParam& param);
	void deinitialize();

  GLContextParam GetContextParam() const {
    return m_contextParam;
  }

  void Display();

  void consume_events(std::function<void()> on_exit,
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
                      std::function<void()> on_restore);
};

#endif
