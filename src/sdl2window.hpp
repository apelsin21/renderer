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

class SDL2Window : public IWindow {
  struct SDL2WindowHandle {
		struct SDLWindowDestroyer {
		    void operator()(SDL_Window* w) const {
		        SDL_DestroyWindow(w);
		    }
		};

		std::unique_ptr<SDL_Window, SDLWindowDestroyer> m_window = nullptr;

    SDL2WindowHandle() {}
    SDL2WindowHandle(const std::string& title, int x, int y,
                     int width, int height) {
      x = x < 0 ? SDL_WINDOWPOS_UNDEFINED : x;
      y = y < 0 ? SDL_WINDOWPOS_UNDEFINED : y;

      m_window = std::unique_ptr<SDL_Window, SDLWindowDestroyer>(
				SDL_CreateWindow(
					title.c_str(),
					x, y,
					width, height,
					SDL_WINDOW_OPENGL
				)
			);

			std::cout << "created window: " << m_window.get() << std::endl;
    }

    int GetWidth() const {
      int width = 0;
      SDL_GetWindowSize(m_window.get(), &width, NULL);
      return width;
    }
    int GetHeight() const {
      int height = 0;
      SDL_GetWindowSize(m_window.get(), NULL, &height);
      return height;
    }

    bool IsValid() const {
      return m_window != nullptr;
    }
    bool IsInvalid() const {
      return m_window == nullptr;
    }

    void Swap() {
      SDL_GL_SwapWindow(m_window.get());
    }

    const auto& GetRaw() const { return m_window; }
    auto& GetRawMut() const { return m_window; }
  };

  struct SDL2ContextHandle {
    SDL_GLContext m_context = NULL;

    SDL2ContextHandle() {}
    SDL2ContextHandle(SDL2WindowHandle& window) {
			std::cout << "context: " << window.GetRaw().get() << std::endl;
      m_context = SDL_GL_CreateContext(window.GetRawMut().get());
    }
    ~SDL2ContextHandle() {
      if(SDL_WasInit(SDL_INIT_VIDEO) && m_context) {
        SDL_GL_DeleteContext(m_context);
      }
    }

    bool IsValid() const {
      return m_context != NULL;
    }
    bool IsInvalid() const {
      return m_context == NULL;
    }

    bool MakeCurrent(SDL2WindowHandle& window) {
			std::cout << "make current: " << window.GetRaw().get() << std::endl;
      return SDL_GL_MakeCurrent(window.GetRawMut().get(), m_context) == 0;
    }

    const SDL_GLContext GetRaw() const { return m_context; }
    SDL_GLContext GetRawMut() const { return m_context; }
  };
protected:
  SDL2WindowHandle m_windowHandle;
  SDL2ContextHandle m_contextHandle;
  GLContextParam m_contextParam;
public:
  SDL2Window() {}

  bool Init();
  bool IsInitialized() const;
  void Deinit();

  bool MakeCurrent();

  bool CreateContext(const GLContextParam& param);

  GLContextParam GetContextParam() const {
    return m_contextParam;
  }

  GLContextParam GetCurrentContextInfo() const;

  void Display();
};

#endif
