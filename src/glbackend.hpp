#ifndef GLBACKEND_HPP
#define GLBACKEND_HPP

#include "sdl2window.hpp"
#include "commandbucket.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include "glshaderloader.hpp"
#include "mesh.hpp"

#include <iostream>
#include <fstream>
#include <memory>

#include <epoxy/gl.h>
#include <FreeImage.h>

class GLBackend {
protected:
  SDL2Window m_window;
  GLShaderLoader m_shaderLoader;

public:
  typedef GLuint TextureHandleType;
  typedef GLuint VertexBufferHandleType;
  typedef GLuint VertexLayoutHandleType;
  typedef GLuint ShaderHandleType;
  typedef GLuint ShaderProgramHandleType;

  template <typename... Args>
  void ConsumeEvents(Args&&... args) {
    m_window.consume_events(args...);
  }

  bool Initialize(GLContextParam& param);

  void Deinitialize();

  void Display();
  
  bool Load(TextureHandleType& texture, const Image& image);
  bool Load(ShaderHandleType& shader, ShaderType type, const std::string& path);
  bool Load(ShaderProgram<GLBackend>* program, const Shader<GLBackend>& vs, const Shader<GLBackend>& fs);

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

  bool AddVertexBufferToMesh(Mesh<GLBackend>* mesh,
                             const std::vector<float>& vertices,
                             GLuint& bufferHandle,
                             const ShaderAttribute& shaderAttribute) const;
  
  void DestroyTexture(TextureHandleType& texture);
  void DestroyVertexBuffer(VertexBufferHandleType& buffer);
  void DestroyVertexLayout(VertexLayoutHandleType& layout);
  void DestroyShader(ShaderHandleType& shader);
  void DestroyShaderProgram(ShaderProgramHandleType& program);

  void Submit(const CommandBucket<unsigned>& bucket);
};

#endif
