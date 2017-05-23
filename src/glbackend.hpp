#ifndef GLBACKEND_HPP
#define GLBACKEND_HPP

#include "sdl2window.hpp"
#include "commandbucket.hpp"
#include "texture.hpp"

#include "epoxy/gl.h"

class GLBackend {
protected:
  SDL2Window m_window;

public:
  typedef GLuint TextureHandleType;
  typedef GLuint VertexBufferHandleType;
  typedef GLuint VertexLayoutHandleType;

  template <typename... Args>
  void ConsumeEvents(Args&&... args) {
    m_window.consume_events(args...);
  }

  bool Initialize(GLContextParam& param);

  void Deinitialize();

  void Display();
  
  void Load(TextureHandleType& texture, const Image& image);

  void Load(
      VertexBufferHandleType& buffer,
      VertexLayoutHandleType& layout,
      const std::vector<float>& vertices);
  
  void Destroy(TextureHandleType& texture);

  void Destroy(
      VertexBufferHandleType& buffer,
      VertexLayoutHandleType& layout);

  void Submit(const CommandBucket<unsigned>& bucket);
};

#endif
