#include "object.h"

namespace Pencil {
    Object::Object()
    {
        setDefaultUV();
    }

    Object::Object(const glm::vec3 & pos, const glm::vec2 & size, glm::vec4 & color)
        : m_Position(pos), m_Size(size), m_Color(color)
    {
        setDefaultUV();
    }

    Object::~Object()
    {
    }

    void Object::setDefaultUV()
    {
        m_UV[0] = glm::vec2(0.0, 0.0);
        m_UV[1] = glm::vec2(0.0, 1.0);
        m_UV[2] = glm::vec2(1.0, 1.0);
        m_UV[3] = glm::vec2(1.0, 0.0);
    }
}