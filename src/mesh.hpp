#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <vector>

template <class GraphicsBackend>
class Mesh {
  typedef typename GraphicsBackend::VertexBufferHandleType VertexBufferHandle;
  typedef typename GraphicsBackend::VertexLayoutHandleType VertexLayoutHandle;
public:

  Mesh(GraphicsBackend& backend) : m_backend(backend) {
  }
  ~Mesh() {
    // should check if it is a valid handle first
    m_backend.DestroyVertexBuffer(m_positionBufferHandle);
    m_backend.DestroyVertexBuffer(m_uvBufferHandle);
    m_backend.DestroyVertexLayout(m_layoutHandle);
  }

  void Load(const std::vector<float>& vertices) {
    m_backend.Load(m_positionBufferHandle, m_layoutHandle, vertices);
  }

  void Load(const std::vector<float>& vertices, const std::vector<float>& uvs) {
    m_backend.Load(m_positionBufferHandle, m_uvBufferHandle, m_layoutHandle, vertices, uvs);
  }

  VertexBufferHandle& GetPositionBufferHandleMutable() {
    return m_positionBufferHandle;
  }
  VertexBufferHandle GetPositionBufferHandle() {
    return m_positionBufferHandle;
  }

  VertexBufferHandle& GetUVBufferHandleMutable() {
    return m_uvBufferHandle;
  }
  VertexBufferHandle GetUVBufferHandle() {
    return m_uvBufferHandle;
  }

  VertexLayoutHandle& GetLayoutHandleMutable() {
    return m_layoutHandle;
  }
  VertexLayoutHandle GetLayoutHandle() {
    return m_layoutHandle;
  }
private:
  GraphicsBackend& m_backend;
  VertexBufferHandle m_positionBufferHandle;
  VertexBufferHandle m_uvBufferHandle;
  VertexLayoutHandle m_layoutHandle;
};

#endif
