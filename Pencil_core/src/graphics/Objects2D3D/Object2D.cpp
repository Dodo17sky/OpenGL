#include "Object2D.h"

namespace Pencil {

    Object2D::Object2D(const glm::vec3& pos, const glm::vec2& size, Shader* shader, glm::vec4& color) :
        m_Position(pos),
        m_Size(size),
        m_Shader(shader),
        m_Color(color),
        m_VAO(nullptr),
        m_EBO(nullptr),
        m_Texture(nullptr)
    {
    }
    Object2D::~Object2D()
    {
        delete m_VAO;
        delete m_EBO;
    }

    bool Object2D::isRendereble() const
    {
        return (
            (m_Shader != nullptr) &&
            (m_VAO != nullptr) &&
            (m_EBO != nullptr)
        );
    }
    
    void Object2D::setDefaultUV()
    {
        m_UV[0] = glm::vec2(0.0, 0.0);
        m_UV[1] = glm::vec2(0.0, 1.0);
        m_UV[2] = glm::vec2(1.0, 1.0);
        m_UV[3] = glm::vec2(1.0, 0.0);
    }
}
