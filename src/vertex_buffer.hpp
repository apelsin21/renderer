#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <vector>

template <class GraphicsBackend>
class VertexBuffer {
  typedef typename GraphicsBackend::VertexBufferHandleType VertexBufferHandle;
  typedef typename GraphicsBackend::VertexLayoutHandleType VertexLayoutHandle;
public:

  VertexBuffer(GraphicsBackend& backend) : m_backend(backend) {
  }
  ~VertexBuffer() {
    // should check if it is a valid handle first
    m_backend.Destroy(m_bufferHandle, m_layoutHandle);
  }

  void Load(const std::vector<float>& vertices) {
    m_backend.Load(m_bufferHandle, m_layoutHandle, vertices);
  }

  VertexBufferHandle GetBufferHandle() {
    return m_bufferHandle;
  }
  VertexBufferHandle GetLayoutHandle() {
    return m_layoutHandle;
  }
private:
  GraphicsBackend& m_backend;
  VertexBufferHandle m_bufferHandle;
  VertexLayoutHandle m_layoutHandle;
};

#endif
