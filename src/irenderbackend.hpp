#ifndef IRENDERBACKEND_HPP
#define IRENDERBACKEND_HPP

#include "commandbucket.hpp"

class IRenderBackend {
public:
  virtual ~IRenderBackend() {}

  virtual void submit(const CommandBucket<unsigned>& bucket) = 0;
};

#endif
