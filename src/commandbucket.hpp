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

  std::shared_ptr<Draw> AllocateCommand() const;
public:
  CommandBucket(int numCommands);

  std::shared_ptr<Draw> AddCommand(Key key);
};

#endif
