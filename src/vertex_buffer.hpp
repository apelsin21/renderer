#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <vector>

template <class GraphicsBackend>
class VertexBuffer {
protected:
  typedef typename GraphicsBackend::VertexBufferHandleType VertexBufferHandle;
  GraphicsBackend& m_backend;
  VertexBufferHandle m_bufferHandle;

public:
  VertexBuffer(GraphicsBackend& backend) : m_backend(backend) {
  }
  ~VertexBuffer() {
    // should check if it is a valid handle first
    m_backend.DestroyVertexBuffer(m_bufferHandle);
  }

  void Load(const std::vector<float>& vertices) {
    m_backend.Load(m_bufferHandle, vertices);
  }

  VertexBufferHandle GetHandle() {
    return m_bufferHandle;
  }
};

#endif
