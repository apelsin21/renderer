#include "glbackend.hpp"

void GLBackend::Submit(const CommandBucket<unsigned>& bucket) {
  for(std::map<unsigned, std::shared_ptr<Draw>>::const_iterator it = bucket.m_drawData.begin(); it != bucket.m_drawData.end(); ++it) {
    std::shared_ptr<Draw> drawCall = it->second;

    glBindVertexArray(drawCall->vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, drawCall->vboID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
       0,
       3,
       GL_FLOAT,
       GL_FALSE,
       0,
       (void*)0
    );

    glUseProgram(drawCall->shaderProgram);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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

void GLBackend::Load(TextureHandleType& texture, const Image& image) {
  std::cout << "loading texture from image " << image.filepath << '\n';
  texture = 1;
}

void GLBackend::Load(
    VertexBufferHandleType& buffer,
    VertexLayoutHandleType& layout,
    const std::vector<float>& vertices) {
  std::cout << "loading vertex buffer from vertices " << vertices.size() << '\n';
  glGenVertexArrays(1, &layout);
  glBindVertexArray(layout);
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, layout);
  const int vertexSize = vertices.size() * sizeof(float);
  glBufferData(GL_ARRAY_BUFFER, vertexSize, &vertices[0], GL_STATIC_DRAW);
}

void GLBackend::Destroy(
    VertexBufferHandleType& buffer,
    VertexLayoutHandleType& layout) {
  std::cout << "destroying buffer " << buffer << "\n";
  std::cout << "destroying layout " << layout << "\n";
  glDeleteBuffers(1, &buffer);
  glDeleteVertexArrays(1, &layout);
}

void GLBackend::Destroy(TextureHandleType& texture) {
  std::cout << "destroying texture " << texture << "\n";
}
