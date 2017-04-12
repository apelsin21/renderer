#ifndef IWINDOW_HPP
#define IWINDOW_HPP

class IWindow {
public:
  virtual ~IWindow() {}

  virtual void Display() = 0;
protected:
  bool m_isInitialized;
};

#endif
