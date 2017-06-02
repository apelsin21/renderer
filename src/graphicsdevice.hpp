#ifndef GRAPHICSDEVICE_HPP
#define GRAPHICSDEVICE_HPP

#include "epoxy/gl.h"

#include "texture.hpp"
#include "commandbucket.hpp"
#include "mesh.hpp"

template <typename GraphicsBackend>
class GraphicsDevice {
  typedef GraphicsDevice<GraphicsBackend> this_type;

public:
  typedef Texture<GraphicsBackend> TextureType;
  typedef Mesh<GraphicsBackend> MeshType;

  template <typename... Args>
  bool Initialize(Args&&... args) {
    return m_backend.Initialize(args...);
  }

  template <typename... Args>
  void ConsumeEvents(Args&&... args) {
    m_backend.ConsumeEvents(args...);
  }

  void Deinitialize() {
    m_backend.Deinitialize();
  }

  void Display() {
    return m_backend.Display();
  }

  template<class T>
  void Submit(const CommandBucket<T>& bucket) {
    m_backend.Submit(bucket);
  }

  //template <typename... Args>
  //TextureType CreateTexture(Args&&... args) {
  //  return TextureType { m_backend, std::forward(args)... };
  //}

  //template <typename... Args>
  //VertexBufferType CreateVertexBuffer(Args&&... args) {
  //  return VertexBufferType { m_backend, std::forward(args)... };
  //}
  
  template <typename Resource, typename... Args>
  Resource Create(Args&&... args) {
    return Resource { m_backend, std::forward(args)... };
  }
private:
  GraphicsBackend m_backend;
};

#endif
