#include "glshader_program.hpp"

std::string GLShaderProgram::LoadTextFile(const std::string& path) {
	std::string text;

	std::ifstream stream(path, std::ios::in);

	if(stream.is_open()) {
		std::string line;

		while(getline(stream, line)) {
			text += "\n" + line;
		}

		stream.close();
	} else {
		std::cerr << "GLShaderProgram failed to load text file \n" << path << std::endl;
	}

	return text;
}

bool GLShaderProgram::CompileShader(GLShaderHandle& handle, const std::string& text) {
	bool successful = false;
	GLint result = GL_FALSE;
	int length = 0;

  const char* textPointer = text.c_str();
	glShaderSource(handle.id, 1, &textPointer, NULL);
	glCompileShader(handle.id);

	glGetShaderiv(handle.id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(handle.id, GL_INFO_LOG_LENGTH, &length);

	if(length) {
		std::vector<char> log(length + 1);
		glGetShaderInfoLog(handle.id, length, NULL, log.data());
		std::cerr << "GLShaderProgram failed to compile shader " << handle.id << " log:"
							<< std::endl << log.data() << std::endl;
	} else {
		successful = true;
	}

	return successful;
}

bool GLShaderProgram::Link() {
	bool linkedSuccessfully = false;
	GLint result = GL_FALSE;
	int length = 0;

	glAttachShader(m_programHandle.id, m_vertexShader.id);
	glAttachShader(m_programHandle.id, m_fragmentShader.id);
	glLinkProgram(m_programHandle.id);

	glGetProgramiv(m_programHandle.id, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programHandle.id, GL_INFO_LOG_LENGTH, &length);

	if(length){
		std::vector<char> log(length + 1);
		glGetProgramInfoLog(m_programHandle.id, length, NULL, log.data());
		std::cerr << "GLShaderProgram failed to link " << m_programHandle.id << " log:"
							<< std::endl << log.data() << std::endl;
	} else {
		linkedSuccessfully = true;
		glDetachShader(m_programHandle.id, m_vertexShader.id);
		glDetachShader(m_programHandle.id, m_fragmentShader.id);
	}

	return linkedSuccessfully;
}

bool GLShaderProgram::Load(const std::string& vertexShaderLocation,
                           const std::string& fragmentShaderLocation) {
	bool loadedSuccessfully = false;

	std::string vertexShaderText = LoadTextFile(vertexShaderLocation);
	std::string fragmentShaderText = LoadTextFile(fragmentShaderLocation);

	if(CompileShader(m_vertexShader, vertexShaderText)) {
		if(CompileShader(m_fragmentShader, fragmentShaderText)) {
			if(Link()) {
				loadedSuccessfully = true;
			}
		}
	}

  return loadedSuccessfully;
}

unsigned int GLShaderProgram::GetProgramId() const {
  return m_programHandle.id;
}

void GLShaderProgram::Use() {
  glUseProgram(m_programHandle.id);
}
