#include <iostream>
#include <vector>

#include <epoxy/gl.h>
#include <epoxy/egl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

using namespace std;

class IContextParam {
public:
  virtual ~IContextParam() {}

  virtual string ToString() const = 0;
};

class GLContextParam : public IContextParam {
public:
  int majorVersion, minorVersion, depthSize;
  bool isCoreProfile, isGLES, isDoubleBuffered;

  GLContextParam(int ma, int mi, int depth,
                 bool core, bool gles, bool doubleBuffered) :
      majorVersion(ma), minorVersion(mi), depthSize(depth),
      isCoreProfile(core), isGLES(gles), isDoubleBuffered(doubleBuffered) {}

  GLContextParam(int ma, int mi, bool core, bool gles) :
      majorVersion(ma), minorVersion(mi), depthSize(24),
      isCoreProfile(core), isGLES(gles), isDoubleBuffered(true) {}

  GLContextParam() : majorVersion(0), minorVersion(0), depthSize(0),
    isCoreProfile(false), isGLES(false), isDoubleBuffered(false) {}

  ~GLContextParam() {
  }

  string ToString() const {
    const string major = to_string(majorVersion);
    const string minor = to_string(minorVersion);
    const string depth = to_string(depthSize);
    const string core = isCoreProfile ? "true" : "false";
    const string gles = isGLES ? "true" : "false";
    const string doubleBuffered = isDoubleBuffered ? "true" : "false";

    return major + "." + minor
      + ", depth: " + depth
      + ", core: " + core
      + ", GLES: " + gles
      + ", double buffered: " + doubleBuffered;
  }
};

class IWindow {
public:
  virtual ~IWindow() {}

  virtual bool Init() = 0;
  virtual bool IsInitialized() const = 0;
protected:
  bool m_isInitialized;
};

class SDL2Window : public IWindow {
protected:
  vector<GLContextParam> GetGLContextParams() const {
    return vector<GLContextParam> {
      GLContextParam(3, 3, true, false),  // 3.3 Core Profile
      GLContextParam(3, 2, true, false),  // 3.2 Core Profile
      GLContextParam(3, 1, false, false), // 3.1
      GLContextParam(3, 0, false, false), // 3.0
      GLContextParam(2, 1, false, false), // 2.1
      GLContextParam(2, 1, false, true),  // 2.1 ES
      GLContextParam(2, 0, false, false), // 2.0
      GLContextParam(2, 0, false, true)   // 2.0 ES
    };
  };

  bool CreateContext(const vector<GLContextParam>& params) {
    bool createdContext = false;

    for(vector<GLContextParam>::const_iterator it = params.begin();
      it < params.end() && !createdContext; ++it) {

      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, it->majorVersion);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, it->minorVersion);
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, it->depthSize);

      if(it->isDoubleBuffered) {
          SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
      } else {
          SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
      }

      if(it->isCoreProfile) {
          SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
      } else if(it->isGLES) {
          SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
      }

      m_sdlWindow = SDL_CreateWindow("OpenGL Test",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      	800, 600, SDL_WINDOW_OPENGL);

      m_sdlContext = SDL_GL_CreateContext(m_sdlWindow);

      if(m_sdlContext) {
        createdContext = true;

        cout << "Created an SDL2 window with OpenGL version: "
             << it->majorVersion << "." << it->minorVersion << endl;

        m_contextParam = *it;
      }
    }

    if(!m_sdlWindow || !m_sdlContext) {
      cout << "SDL2Window could not create OpenGL context. Error: "
           << SDL_GetError() << endl;
    }

    return createdContext;
  }

  SDL_Window* m_sdlWindow;
  SDL_GLContext m_sdlContext;
  GLContextParam m_contextParam;
public:
  SDL2Window() {
    m_isInitialized = false;
    m_sdlWindow = nullptr;
    m_sdlContext = NULL;

    m_contextParam = GLContextParam(0, 0, false, false);
  }
  ~SDL2Window() {
    if(m_sdlWindow) {
      SDL_DestroyWindow(m_sdlWindow);
    }

    if(m_sdlContext) {
      SDL_GL_DeleteContext(m_sdlContext);
    }

    SDL_Quit();
  }

  bool Init() {
    if(IsInitialized()) {
      return false;
    }

    const vector<GLContextParam> params = GetGLContextParams();

    //If the return value isn't zero, SDL is initialized.
    bool sdlIsInitialized = SDL_WasInit(SDL_INIT_VIDEO) == 0 ? false : true;

    if(sdlIsInitialized) {
      cout << "SDL2 was already initialized during init.\n";
    } else if(SDL_Init(SDL_INIT_VIDEO) < 0) {
      cout << "Unable to initialize SDL2. Error: " << SDL_GetError() << endl;
      return false;
    }

    bool createdContext = CreateContext(params);

    if(createdContext) {
      int err = SDL_GL_MakeCurrent(m_sdlWindow, m_sdlContext);

      if(err == 0) {
        m_isInitialized = true;
      } else {
        cout << "Failed to make SDL2 OpenGL context current. Error: "
             << SDL_GetError() << endl;

        createdContext = false;
      }
    }

    return createdContext;
  }
  bool IsInitialized() const {
    return m_isInitialized;
  }

  GLContextParam GetContextParam() const {
    return m_contextParam;
  }
};

int main(void) {
  SDL2Window window;

  if(window.Init()) {
    GLContextParam param = window.GetContextParam();
    string paramString = param.ToString();

    cout << paramString << endl;

    cout << "Epoxy OpenGL version: " << epoxy_gl_version() << endl;
    cout << "GL_VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << endl;
  } else {
    cout << "Failed to intialize SDL2 window.\n";
    return -1;
  }

  return 0;
}
