#ifndef GRAPHICSDEVICE_HPP
#define GRAPHICSDEVICE_HPP

#include "texture.hpp"
#include "commandbucket.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include "shader_attribute.hpp"

template <typename GraphicsBackend>
class GraphicsDevice {
  typedef GraphicsDevice<GraphicsBackend> this_type;

public:
  typedef Texture<GraphicsBackend> TextureType;
  typedef Mesh<GraphicsBackend> MeshType;
  typedef Shader<GraphicsBackend> ShaderType;
  typedef ShaderProgram<GraphicsBackend> ShaderProgramType;

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

  template <typename Resource, typename... Args>
  Resource Create(Args&&... args) {
    return Resource { m_backend, args... };
  }
private:
  GraphicsBackend m_backend;
};

#endif
