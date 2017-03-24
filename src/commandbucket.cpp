#include "commandbucket.hpp"

template <typename T> 
CommandBucket<T>::CommandBucket(int numCommands) {
  m_drawData.reserve(numCommands);
}

template <typename T> 
std::shared_ptr<Draw> CommandBucket<T>::AllocateCommand() const {
  return std::make_shared<Draw>();
}

template <typename T> 
std::shared_ptr<Draw> CommandBucket<T>::AddCommand(Key key) {
  std::shared_ptr<Draw> data = AllocateCommand();

  m_drawData[key] = data;

  return data;
}
