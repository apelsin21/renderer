#ifndef SDL2WINDOW_HPP
#define SDL2WINDOW_HPP

#include <vector>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "glcontextparam.hpp"
#include "iwindow.hpp"

class SDL2Window : public IWindow {
protected:
  SDL_Window* m_sdlWindow;
  SDL_GLContext m_sdlContext;
  GLContextParam m_contextParam;
public:
  SDL2Window() : m_sdlWindow(nullptr), m_sdlContext(NULL) {}
  ~SDL2Window();

  bool Init();
  bool IsInitialized() const;
  void Deinit();

  bool MakeCurrent();

  bool CreateContext(const std::vector<GLContextParam>& params);

  GLContextParam GetContextParam() const {
    return m_contextParam;
  }

  void Display();
};

#endif
