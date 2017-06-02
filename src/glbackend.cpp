#include "glbackend.hpp"

void GLBackend::Submit(const CommandBucket<unsigned>& bucket) {
  for(std::map<unsigned, std::shared_ptr<Draw>>::const_iterator it = bucket.m_drawData.begin(); it != bucket.m_drawData.end(); ++it) {
    std::shared_ptr<Draw> call = it->second;

    glBindVertexArray(call->vaoID);
    glBindTexture(GL_TEXTURE_2D, call->textureID);
    glUseProgram(call->shaderProgram);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

  FIBITMAP* fb = nullptr;
  FREE_IMAGE_FORMAT ff = FreeImage_GetFileType(image.filepath.c_str(), 0);

	if(ff == FIF_UNKNOWN) {
		ff = FreeImage_GetFIFFromFilename(image.filepath.c_str());
	}

	if(ff != FIF_UNKNOWN && FreeImage_FIFSupportsReading(ff)) {
		fb = FreeImage_Load(ff, image.filepath.c_str());
	} else {
    std::cerr << "tried to load texture "
              << image.filepath
              << ", but the format is "
				      << "unsupported by FreeImage.\n";

		return false;
	}

	if(FreeImage_GetBPP(fb) != 32) {
  	FIBITMAP* temp = fb;
  	fb = FreeImage_ConvertTo32Bits(temp);
  	FreeImage_Unload(temp);
	}

	if(FreeImage_GetBits(fb) == nullptr) {
    std::cerr << "data loaded by FreeImage is null for unknown reason.\n";
		return false;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA8,
		FreeImage_GetWidth(fb), FreeImage_GetHeight(fb),
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		(GLvoid*)FreeImage_GetBits(fb)
	);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	FreeImage_Unload(fb);

	return true;
}

void GLBackend::Load(
    VertexBufferHandleType& buffer,
    VertexLayoutHandleType& layout,
    const std::vector<float>& vertices) {
  std::cout << "loading vertex buffer from vertices " << vertices.size() << '\n';
  glGenVertexArrays(1, &layout);
  glBindVertexArray(layout);
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  const int vertexSize = vertices.size() * sizeof(float);
  glBufferData(GL_ARRAY_BUFFER, vertexSize, &vertices[0], GL_STATIC_DRAW);
}

void GLBackend::Load(
    VertexBufferHandleType& posBuffer,
    VertexBufferHandleType& uvBuffer,
    VertexLayoutHandleType& layout,
    const std::vector<float>& pos,
    const std::vector<float>& uvs) {
  std::cout << "loading pos buffer from " << pos.size() << " floats\n";
  std::cout << "loading uv buffer from " << uvs.size() << " floats\n";
  glGenVertexArrays(1, &layout);
  glBindVertexArray(layout);

  glGenBuffers(1, &posBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
  const unsigned int posSize = pos.size() * sizeof(float);
  glBufferData(GL_ARRAY_BUFFER, posSize, &pos[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glGenBuffers(1, &uvBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  const unsigned int uvSize = uvs.size() * sizeof(float);
  glBufferData(GL_ARRAY_BUFFER, uvSize, &uvs[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
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

