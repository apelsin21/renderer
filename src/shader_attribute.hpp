#ifndef SHADER_ATTRIBUTE_HPP
#define SHADER_ATTRIBUTE_HPP

#include <string>

enum class ShaderAttributeType : unsigned int {
  None = 0,
  Float = 1,
  Vec2 = 2,
  Vec3 = 3,
  Vec4 = 4,
  Mat3 = 9,
  Mat4 = 16,
  Mat2x4 = 8,
  Mat3x4 = 12,
  Max
};

class ShaderAttribute {
  protected:
    std::string m_name;
    ShaderAttributeType m_type;
    unsigned int m_size;
    unsigned int m_location;
  public:
    ShaderAttribute() : m_type(ShaderAttributeType::None), m_size(0), m_location(0) {}

    ShaderAttribute(const std::string& name,
                    const ShaderAttributeType& type,
                    const unsigned size,
                    const unsigned location)
      : m_name(name), m_type(type), m_size(size), m_location(location) {
    }
    ~ShaderAttribute() {
    }

    std::string GetName() const { return m_name; }
    ShaderAttributeType GetType() const { return m_type; }
    unsigned int GetLocation() const { return m_location; }
};

#endif
