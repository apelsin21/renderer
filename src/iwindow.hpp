#ifndef IWINDOW_HPP
#define IWINDOW_HPP

class IWindow {
public:
  virtual ~IWindow() {}

  virtual bool Init() = 0;
  virtual bool IsInitialized() const = 0;
protected:
  bool m_isInitialized;
};

#endif
