#ifndef COMMAND_BUCKET_TEST_HPP
#define COMMAND_BUCKET_TEST_HPP

#include "catch.hpp"

#include "epoxy/gl.h"

#include "commandbucket.hpp"
#include "sdl2window.hpp"
#include "glbackend.hpp"
#include "graphicsdevice.hpp"
#include "texture.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "shader_program.hpp"

class GLGraphicsDevice : public GraphicsDevice<GLBackend> {
public:
  enum class feature {
    texturing
  };

  void EnableFeature(feature f) {
    std::cout << "enabling feature... " << (int)f << '\n';
  }
};

#endif
