#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <vector>
#include <string>

#include "shader.hpp"

template <class GraphicsBackend>
class ShaderProgram {
  typedef typename GraphicsBackend::ShaderProgramHandleType ShaderProgramHandle;
protected:
  GraphicsBackend& m_backend;
  ShaderProgramHandle m_handle;

public:
  ShaderProgram(GraphicsBackend& backend) : m_backend(backend) {
	}
  ~ShaderProgram() {
    m_backend.DestroyShaderProgram(m_handle);
	}

  bool Load(const Shader<GraphicsBackend>& vertexShader, const Shader<GraphicsBackend>& fragmentShader) {
    return m_backend.Load(m_handle, vertexShader, fragmentShader);
  }

  ShaderProgramHandle GetHandle() const {
    return m_handle;
  }
};

#endif
