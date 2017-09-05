#ifndef GLSHADERLOADER_HPP
#define GLSHADERLOADER_HPP

#include "defines.hpp"

class GLBackend;

template<class GLBackend>
class ShaderProgram;

template<class GLBackend>
class Shader;

class GLShaderLoader {
  public:
    ~GLShaderLoader() {}

    bool LoadShader(GLuint& shader,
                    const ShaderType type,
                    const std::string& path) const;

    bool LoadShaderProgram(ShaderProgram<GLBackend>* program,
                           const Shader<GLBackend>& vs,
                           const Shader<GLBackend>& fs) const;

  protected:
    std::vector<ShaderAttribute> GetActiveAttributes(const GLuint programId) const;
    ShaderAttributeType ConvertGLAttributeType(const GLenum type) const;
};

#endif
