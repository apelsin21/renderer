#ifndef SDL2WINDOW_HPP
#define SDL2WINDOW_HPP

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "iwindow.hpp"

#include "glcontextparam.hpp"

class SDL2Window : public IWindow {
protected:
  std::vector<GLContextParam> GetGLContextParams() const;

  bool CreateContext(const std::vector<GLContextParam>& params);

  SDL_Window* m_sdlWindow;
  SDL_GLContext m_sdlContext;
  GLContextParam m_contextParam;
public:
  SDL2Window() {
    m_isInitialized = false;
    m_sdlWindow = nullptr;
    m_sdlContext = NULL;

    m_contextParam = GLContextParam(0, 0, false, false);
  }
  ~SDL2Window() {
    if(m_sdlWindow) {
      SDL_DestroyWindow(m_sdlWindow);
    }

    if(m_sdlContext) {
      SDL_GL_DeleteContext(m_sdlContext);
    }

    SDL_Quit();
  }

  bool Init();
  bool IsInitialized() const {
    return m_isInitialized;
  }

  GLContextParam GetContextParam() const {
    return m_contextParam;
  }
};

#endif
