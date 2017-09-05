#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>

#include "defines.hpp"

template <class GraphicsBackend>
class Shader {
  typedef typename GraphicsBackend::ShaderHandleType ShaderHandle;

  protected:
    GraphicsBackend& m_backend;
    ShaderHandle m_handle;
    ShaderType m_type;

  public:
    Shader(GraphicsBackend& backend, ShaderType type) : m_backend(backend), m_type(type) {
    }
    ~Shader() {
      m_backend.DestroyShader(m_handle);
    }

    bool Load(const std::string& path) {
      return m_backend.Load(m_handle, m_type, path);
    }

    ShaderHandle GetHandle() const {
      return m_handle;
    }
};

#endif
