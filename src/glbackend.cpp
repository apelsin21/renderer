#include "glbackend.hpp"

void GLBackend::Submit(const CommandBucket<unsigned>& bucket) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for(const auto& pair : bucket.m_drawData) {
    std::shared_ptr<Draw> call = pair.second;

    glBindVertexArray(call->vaoID);
    glBindTexture(GL_TEXTURE_2D, call->textureID);
    glUseProgram(call->shaderProgram);

    glDrawArrays(GL_TRIANGLES, call->startVertex, call->vertexCount);
  }
}

bool GLBackend::Initialize(GLContextParam& param) {
  std::cout << "GLBackend initializing using: " << param.to_string() << '\n';
  return m_window.initialize(param);
}

void GLBackend::Deinitialize() {
  std::cout << "GLBackend deinitializing\n";
  m_window.deinitialize();
}

void GLBackend::Display() {
  m_window.Display();
}

bool GLBackend::Load(TextureHandleType& texture, const Image& image) {
  std::cout << "loading texture from image " << image.filepath << '\n';

  bool ok = false;
  FIBITMAP* bitmap = nullptr;
  FREE_IMAGE_FORMAT format = FreeImage_GetFileType(image.filepath.c_str(), 0);

	if(format == FIF_UNKNOWN) {
		format = FreeImage_GetFIFFromFilename(image.filepath.c_str());
	}

	if(format != FIF_UNKNOWN && FreeImage_FIFSupportsReading(format)) {
		bitmap = FreeImage_Load(format, image.filepath.c_str());
    ok = true;
	} else {
    std::cerr << "tried to load texture "
              << image.filepath
              << ", but the format is "
				      << "unsupported by FreeImage.\n";
	}

	if(ok && FreeImage_GetBPP(bitmap) != 32) {
  	FIBITMAP* temp = bitmap;
  	bitmap = FreeImage_ConvertTo32Bits(temp);
  	FreeImage_Unload(temp);
	}

	if(ok && FreeImage_GetBits(bitmap) == nullptr) {
    std::cerr << "data loaded by FreeImage is null for unknown reason.\n";
    ok = false;
	}

  if(ok) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RGBA8,
      FreeImage_GetWidth(bitmap),
      FreeImage_GetHeight(bitmap),
      0,
      GL_BGRA,
      GL_UNSIGNED_BYTE,
      (GLvoid*)FreeImage_GetBits(bitmap)
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    FreeImage_Unload(bitmap);
  }

	return ok;
}

void GLBackend::Load(
    VertexBufferHandleType& buffer,
    VertexLayoutHandleType& layout,
    const std::vector<float>& vertices) {
  const int vertexSize = vertices.size() * sizeof(float);

  glGenVertexArrays(1, &layout);
  glGenBuffers(1, &buffer);

  std::cout << "loading vao " << layout << std::endl;
  std::cout << "loading buffer " << buffer << " from " << vertices.size() << " floats\n";

  glBindVertexArray(layout);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);

  glBufferData(GL_ARRAY_BUFFER, vertexSize, &vertices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void GLBackend::Load(
    VertexBufferHandleType& posBuffer,
    VertexBufferHandleType& uvBuffer,
    VertexLayoutHandleType& layout,
    const std::vector<float>& pos,
    const std::vector<float>& uvs) {

  const unsigned int posSize = pos.size() * sizeof(float);
  const unsigned int uvSize = uvs.size() * sizeof(float);

  glGenVertexArrays(1, &layout);
  glGenBuffers(1, &posBuffer);
  glGenBuffers(1, &uvBuffer);

  std::cout << "loading vao " << layout << std::endl;
  std::cout << "loading pos buffer " << posBuffer << " from " << pos.size() << " floats\n";
  std::cout << "loading uv buffer " << uvBuffer << " from " << uvs.size() << " floats\n";

  glBindVertexArray(layout);

  glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
  glBufferData(GL_ARRAY_BUFFER, posSize, &pos[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glBufferData(GL_ARRAY_BUFFER, uvSize, &uvs[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

bool GLBackend::Load(ShaderHandleType& shader, ShaderType type, const std::string& path) {
  return m_shaderLoader.LoadShader(shader, type, path);
}

bool GLBackend::Load(ShaderProgram<GLBackend>* shaderProgram, const Shader<GLBackend>& vs, const Shader<GLBackend>& fs) {
  return m_shaderLoader.LoadShaderProgram(shaderProgram, vs, fs);
}

void GLBackend::DestroyTexture(TextureHandleType& texture) {
  std::cout << "destroying texture " << texture << "\n";
  glDeleteTextures(1, &texture);
}

void GLBackend::DestroyVertexBuffer(VertexBufferHandleType& buffer) {
  std::cout << "destroying buffer " << buffer << "\n";
  glDeleteBuffers(1, &buffer);
}

void GLBackend::DestroyVertexLayout(VertexLayoutHandleType& layout) {
  std::cout << "destroying layout " << layout << "\n";
  glDeleteVertexArrays(1, &layout);
}

void GLBackend::DestroyShader(ShaderHandleType& shader) {
  std::cout << "destroying shader " << shader << std::endl;
  glDeleteShader(shader);
}

void GLBackend::DestroyShaderProgram(ShaderProgramHandleType& shaderProgram) {
  std::cout << "destroying shader program " << shaderProgram << std::endl;
  glDeleteProgram(shaderProgram);
}
