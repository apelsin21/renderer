#include <iostream>
#include <fstream>
#include <vector>

#include "epoxy/gl.h"

#include "shader_program.hpp"
#include "shader.hpp"
#include "glbackend.hpp"

#include "glshaderloader.hpp"

using namespace std;

bool GLShaderLoader::LoadShader(GLuint& shader,
                                const ShaderType type,
                                const std::string& path) const {
  if(type == ShaderType::Vertex) {
    shader = glCreateShader(GL_VERTEX_SHADER);
  } else if(type == ShaderType::Fragment) {
    shader = glCreateShader(GL_FRAGMENT_SHADER);
  }

  std::cout << "Loading shader " << shader << " from file " << path << std::endl;

	std::string text;
  std::string line;
	std::ifstream stream(path, std::ios::in);
  GLint compiledSuccessfully = 0;
  bool ok = false;
	int length = 0;

	if(stream.is_open()) {
		while(getline(stream, line)) {
			text += "\n" + line;
		}

		stream.close();
    ok = true;
	} else {
		std::cerr << "GLBackend failed to load text file " << path << std::endl;
    ok = false;
	}

  if(ok) {
    const char* textPointer = text.c_str();
    glShaderSource(shader, 1, &textPointer, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiledSuccessfully);

    if(compiledSuccessfully) {
      ok = true;
    } else {
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
      std::vector<char> log(length + 1);
      glGetShaderInfoLog(shader, length, NULL, log.data());

      std::cerr << "GLShaderProgram failed to compile shader "
                << shader
                << " log:"
                << std::endl
                << log.data()
                << std::endl;
      ok = false;
    }
  }

	return ok;
}

bool GLShaderLoader::LoadShaderProgram(ShaderProgram<GLBackend>* shaderProgram,
                                       const Shader<GLBackend>& vs,
                                       const Shader<GLBackend>& fs) const {
  if(glIsProgram(shaderProgram->GetHandle())) {
    glDeleteProgram(shaderProgram->GetHandle());
  }

  GLuint programId = 0;
	GLint result = GL_FALSE;
	int length = 0;
  const GLuint vsId = vs.GetHandle();
  const GLuint fsId = fs.GetHandle();

  programId = glCreateProgram();
	glAttachShader(programId, vsId);
	glAttachShader(programId, fsId);
	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &result);

	if(result) {
    shaderProgram->AddAttributes(GetActiveAttributes(programId));

		glDetachShader(programId, vsId);
		glDetachShader(programId, fsId);
	} else {
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length + 1);
		glGetProgramInfoLog(programId, length, NULL, log.data());

		std::cerr << "GLShaderProgram failed to link "
              << programId
              << " log:"
							<< std::endl
              << log.data()
              << std::endl;
	}

  //Independently of whether we're successful or not, we'll update the shader program's
  //internal handle.
  shaderProgram->SetHandle(programId);

	return result;
}

std::vector<ShaderAttribute>
GLShaderLoader::GetActiveAttributes(const GLuint programId) const {
  GLint attributeCount = 0;
  GLint uniformCount = 0;
  glGetProgramiv(programId, GL_ACTIVE_ATTRIBUTES, &attributeCount);
  glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &uniformCount);

  char buffer[128];
  GLenum type = 0;
  GLsizei size = 0;

  vector<ShaderAttribute> attributes(attributeCount + uniformCount);

  for(int i = 0; i < attributeCount; i++) {
    glGetActiveAttrib(programId, i, sizeof(buffer), 0, &size, &type, buffer);
    const GLuint location = glGetAttribLocation(programId, buffer);

    const ShaderAttributeType attribType = ConvertGLAttributeType(type);
    const ShaderAttribute attribute(buffer, attribType, size);
    attributes.emplace_back(attribute);

    std::cout << "found attribute " << buffer << " @ " << location << std::endl;
  }

  for(int i = 0; i < uniformCount; i++) {
    glGetActiveUniform(programId, i, sizeof(buffer), 0, &size, &type, buffer);
    const GLuint location = glGetUniformLocation(programId, buffer);

    const ShaderAttributeType uniformType = ConvertGLAttributeType(type);
    const ShaderAttribute uniform(buffer, uniformType, size);
    attributes.emplace_back(uniform);

    std::cout << "found uniform " << buffer << " @ " << location << std::endl;
  }

  return attributes;
}

ShaderAttributeType GLShaderLoader::ConvertGLAttributeType(const GLenum type) const {
  switch(type) {
    case GL_FLOAT:        return ShaderAttributeType::Float;
    case GL_FLOAT_VEC2:   return ShaderAttributeType::Vec2;
    case GL_FLOAT_VEC3:   return ShaderAttributeType::Vec3;
    case GL_FLOAT_VEC4:   return ShaderAttributeType::Vec4;
    case GL_FLOAT_MAT2:   return ShaderAttributeType::Mat2;
    case GL_FLOAT_MAT3:   return ShaderAttributeType::Mat3;
    case GL_FLOAT_MAT4:   return ShaderAttributeType::Mat4;
    case GL_FLOAT_MAT2x4: return ShaderAttributeType::Mat2x4;
    case GL_FLOAT_MAT3x4: return ShaderAttributeType::Mat3x4;
    case GL_FLOAT_MAT4x2: return ShaderAttributeType::Mat4x2;
    case GL_FLOAT_MAT4x3: return ShaderAttributeType::Mat4x3;
    default:              return ShaderAttributeType::None;
  }
}
