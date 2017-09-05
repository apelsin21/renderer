#ifndef ISHADERLOADER_HPP
#define ISHADERLOADER_HPP

class ShaderHandleType;

class IShaderLoader {
  public:
    virtual ~IShaderLoader() {}

    virtual bool LoadShader(ShaderHandleType& shader,
                    const ShaderType type,
                    const std::string& path) const = 0;
};

#endif
