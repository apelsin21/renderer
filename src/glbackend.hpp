#ifndef GLBACKEND_HPP
#define GLBACKEND_HPP

#include "sdl2window.hpp"
#include "commandbucket.hpp"
#include "texture.hpp"

#include <epoxy/gl.h>
#include <FreeImage.h>

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
  
  bool Load(TextureHandleType& texture, const Image& image);

  void Load(
      VertexBufferHandleType& buffer,
      VertexLayoutHandleType& layout,
      const std::vector<float>& vertices);

  void Load(
      VertexBufferHandleType& posBuffer,
      VertexBufferHandleType& uvBuffer,
      VertexLayoutHandleType& layout,
      const std::vector<float>& vertices,
      const std::vector<float>& uvs);
  
  void DestroyTexture(TextureHandleType& texture);
  void DestroyVertexBuffer(VertexBufferHandleType& buffer);
  void DestroyVertexLayout(VertexLayoutHandleType& layout);

  void Submit(const CommandBucket<unsigned>& bucket);
};

#endif
