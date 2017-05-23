#ifndef GLSHADER_PROGRAM_HPP
#define GLSHADER_PROGRAM_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "ishader_program.hpp"

#include "epoxy/gl.h"

enum class ShaderType {
  vertex,
  fragment,
  geometry,
  max
};

class GLShaderProgram : public IShaderProgram {
  struct GLShaderHandle {
    GLuint id = 0;
		ShaderType type = ShaderType::max;

    GLenum MapShaderTypeToNative(ShaderType type) {
      switch(type) {
        case ShaderType::vertex: return GL_VERTEX_SHADER;
        case ShaderType::fragment: return GL_FRAGMENT_SHADER;
        case ShaderType::geometry: return GL_GEOMETRY_SHADER;
        default: return GL_INVALID_ENUM;
      }
    }

		void Create(ShaderType t) {
			id = glCreateShader(MapShaderTypeToNative(t));
			type = t;
		}
		void Delete() {
			glDeleteShader(id);
			id = 0;
		}
  };

  struct GLShaderProgramHandle {
    GLuint id = 0;

    GLShaderProgramHandle() {
     id = glCreateProgram();
    }
    ~GLShaderProgramHandle() {
      glDeleteProgram(id);
    }
  };
protected:
  GLShaderHandle m_vertexShader;
  GLShaderHandle m_fragmentShader;
  GLShaderProgramHandle m_programHandle;

  std::string LoadTextFile(const std::string& path);
  bool CompileShader(GLShaderHandle& handle, const std::string& text);
	bool Link();
public:
  GLShaderProgram() {
		m_vertexShader.Create(ShaderType::vertex);
		m_fragmentShader.Create(ShaderType::fragment);
	}
  ~GLShaderProgram() {
		m_vertexShader.Delete();
		m_fragmentShader.Delete();
	}

  bool Load(const std::string& vertexShaderLocation,
            const std::string& fragmentShaderLocation);

  unsigned int GetProgramId() const;

	void Use();
};

#endif
