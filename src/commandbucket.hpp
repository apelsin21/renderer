#ifndef COMMAND_BUCKET_HPP
#define COMMAND_BUCKET_HPP

#include <map>
#include <memory>

#include <epoxy/gl.h>

struct Draw {
  unsigned int vertexCount, startVertex;

  GLuint vaoID, vboID, shaderProgram;
};

template <typename T>
class CommandBucket {
  typedef T Key;
protected:
  std::map<Key, std::shared_ptr<Draw>> m_drawData;

  std::shared_ptr<Draw> AllocateCommand() const {
    return std::make_shared<Draw>();
  }

  int m_numCommands = 0;
public:
  CommandBucket(int numCommands) {
    m_numCommands = numCommands;
  }

  std::shared_ptr<Draw> AddCommand(Key key) {
    std::shared_ptr<Draw> data = AllocateCommand();

    m_drawData[key] = data;

    return data;
  }
};

#endif
