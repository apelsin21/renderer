#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <iostream>
#include <vector>

#include "shader_attribute.hpp"

template <class GraphicsBackend>
class Mesh {
  typedef typename GraphicsBackend::VertexBufferHandleType VertexBufferHandle;
  typedef typename GraphicsBackend::VertexLayoutHandleType VertexLayoutHandle;
public:

  Mesh(GraphicsBackend& backend) : m_backend(backend) {
  }
  ~Mesh() {
    for(auto& vertexBufferHandle : m_vertexBufferHandles) {
      m_backend.DestroyVertexBuffer(vertexBufferHandle);
    }

    // should check if it is a valid handle first
    m_backend.DestroyVertexLayout(m_layoutHandle);
  }

  //void Load(const std::vector<float>& vertices) {
  //  m_backend.Load(m_positionBufferHandle, m_layoutHandle, vertices);
  //}

  //void Load(const std::vector<float>& vertices, const std::vector<float>& uvs) {
  //  m_backend.Load(m_positionBufferHandle, m_uvBufferHandle, m_layoutHandle, vertices, uvs);
  //}

  bool Add(const std::vector<float>& vertices, const ShaderAttribute& attribute) {
    VertexBufferHandle newBuffer = 0;

    const bool success = m_backend.AddVertexBufferToMesh(this, vertices, newBuffer, attribute);

    if(success) {
      m_vertexBufferHandles.emplace_back(newBuffer);
      std::cout << "adding new buffer " << newBuffer << " to mesh" << std::endl;
    }

    return success;
  }

  VertexLayoutHandle& GetLayoutHandleMutable() {
    return m_layoutHandle;
  }
  VertexLayoutHandle GetLayoutHandle() {
    return m_layoutHandle;
  }
private:
  GraphicsBackend& m_backend;

  std::vector<VertexBufferHandle> m_vertexBufferHandles;
  VertexLayoutHandle m_layoutHandle;
};

#endif
