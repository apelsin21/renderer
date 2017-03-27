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
    SDL_Window* m_window = nullptr;

    SDL2WindowHandle() {}
    ~SDL2WindowHandle() {
      if(m_window) {
        SDL_DestroyWindow(m_window);
      }
    }

    SDL2WindowHandle(const std::string& title, int x, int y,
                     int width, int height) {
      x = x < 0 ? SDL_WINDOWPOS_UNDEFINED : x;
      y = y < 0 ? SDL_WINDOWPOS_UNDEFINED : y;
      m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL);
    }

    int GetWidth() const {
      int width = 0;
      SDL_GetWindowSize(m_window, &width, NULL);
      return width;
    }
    int GetHeight() const {
      int height = 0;
      SDL_GetWindowSize(m_window, NULL, &height);
      return height;
    }

    bool IsValid() const {
      return m_window;
    }
    bool IsInvalid() const {
      return m_window == nullptr;
    }

    void Swap() {
      SDL_GL_SwapWindow(m_window);
    }

    const SDL_Window* GetRaw() const { return m_window; }
    SDL_Window* GetRawMut() const { return m_window; }
  };

  struct SDL2ContextHandle {
    SDL_GLContext m_context = NULL;

    SDL2ContextHandle() {}
    SDL2ContextHandle(SDL2WindowHandle& windowHandle) {
      m_context = SDL_GL_CreateContext(windowHandle.GetRawMut());
    }
    ~SDL2ContextHandle() {
      if(m_context) {
        SDL_GL_DeleteContext(m_context);
      }
    }

    bool IsValid() const {
      return m_context;
    }
    bool IsInvalid() const {
      return m_context == NULL;
    }

    bool MakeCurrent(SDL2WindowHandle& window) {
      return SDL_GL_MakeCurrent(window.GetRawMut(), m_context) == 0;
    }

    const SDL_GLContext GetRaw() const { return m_context; }
    SDL_GLContext GetRawMut() const { return m_context; }
  };
protected:
  SDL2WindowHandle m_sdlWindow;
  SDL2ContextHandle m_sdlContext;
  GLContextParam m_contextParam;
public:
  SDL2Window() {}

  bool Init();
  bool IsInitialized() const;
  void Deinit();

  bool MakeCurrent();

  bool CreateContext(const std::vector<GLContextParam>& params);

  GLContextParam GetContextParam() const {
    return m_contextParam;
  }

  GLContextParam GetCurrentContextInfo() const;

  void Display();
};

#endif
