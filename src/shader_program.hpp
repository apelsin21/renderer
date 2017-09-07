#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <vector>
#include <string>

#include "shader.hpp"
#include "shader_attribute.hpp"

template <class GraphicsBackend>
class ShaderProgram {
  typedef typename GraphicsBackend::ShaderProgramHandleType ShaderProgramHandle;
protected:
  GraphicsBackend& m_backend;
  ShaderProgramHandle m_handle;
  std::vector<ShaderAttribute> m_attributes;
  std::vector<ShaderAttribute> m_uniforms;

public:
  ShaderProgram(GraphicsBackend& backend) : m_backend(backend) {
	}
  ~ShaderProgram() {
    m_backend.DestroyShaderProgram(m_handle);
	}

  bool Load(const Shader<GraphicsBackend>& vertexShader, const Shader<GraphicsBackend>& fragmentShader) {
    return m_backend.Load(this, vertexShader, fragmentShader);
  }
  
  void AddAttributes(const std::vector<ShaderAttribute>& attributes) {
    m_attributes.insert(m_attributes.end(), attributes.begin(), attributes.end());
  }

  void AddUniforms(const std::vector<ShaderAttribute>& uniforms) {
    m_uniforms.insert(m_uniforms.end(), uniforms.begin(), uniforms.end());
  }
  std::vector<ShaderAttribute> GetAttributes() const {
    return m_attributes;
  }

  std::vector<ShaderAttribute> GetUniforms() const {
    return m_uniforms;
  }

  ShaderProgramHandle GetHandle() const {
    return m_handle;
  }
  void SetHandle(const ShaderProgramHandle& handle) {
    m_handle = handle;
  }
};

#endif
