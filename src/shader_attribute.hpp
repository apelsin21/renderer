#ifndef SHADER_ATTRIBUTE_HPP
#define SHADER_ATTRIBUTE_HPP

#include <string>

enum class ShaderAttributeType {
  None,
  Float,
  Vec2,
  Vec3,
  Vec4,
  Mat2,
  Mat3,
  Mat4,
  Mat2x4,
  Mat3x4,
  Mat4x2,
  Mat4x3,
  Max
};

class ShaderAttribute {
  protected:
    std::string m_name;
    ShaderAttributeType m_type;
    unsigned int m_size;
  public:
    ShaderAttribute() : m_type(ShaderAttributeType::None), m_size(0) {}

    ShaderAttribute(const std::string& name,
                    const ShaderAttributeType& type,
                    const unsigned size)
      : m_name(name), m_type(type), m_size(size) {
    }
    ~ShaderAttribute() {
    }

    std::string GetName() const { return m_name; }
    ShaderAttributeType GetType() const { return m_type; }
};

#endif
