#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

struct Image {
  std::string filepath;
};

template <class GraphicsBackend>
class Texture {
  typedef typename GraphicsBackend::TextureHandleType TextureHandle;

protected:
  GraphicsBackend& m_backend;
  TextureHandle m_handle;

public:

  Texture(GraphicsBackend& backend) : m_backend(backend) {
  }
  ~Texture() {
    // should check if it is a valid handle first
    m_backend.DestroyTexture(m_handle);
  }

  bool Load(const Image& image) {
    return m_backend.Load(m_handle, image);
  }

  TextureHandle GetHandle() const {
    return m_handle;
  }
};

#endif
