#include "sdl2window.hpp"

void SDL2Window::Display() {
	m_sdlContextHandle.Swap(m_sdlWindowHandle);
}
