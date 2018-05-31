#include "Object2D.h"

namespace Pencil {
    Object2D::Object2D(const glm::vec3& pos, const glm::vec2& size, Shader* shader, glm::vec4& color) :
        m_Position(pos),
        m_Size(size),
        m_Shader(shader),
        m_Color(color)
    {
        GLfloat vertices[] = {
            pos.x+0.0f,     pos.y+0.0f,     pos.z+0.0f,
            pos.x+0.0f,     pos.y+size.y,   pos.z+0.0f,
            pos.x+size.x,   pos.y+size.y,   pos.z+0.0f,
            pos.x+size.x,   pos.y+0.0f,     pos.z+0.0f
        };

        GLfloat colors[] = {
            color.r, color.g, color.b, color.a,
            color.r, color.g, color.b, color.a,
            color.r, color.g, color.b, color.a,
            color.r, color.g, color.b, color.a
        };

        GLushort indices[] = {
            0, 1, 2, 0, 2, 3
        };

        m_VAO = new VertexArray();
        m_EBO = new IndexBuffer(indices, 6);

        Buffer* vBuf = new Buffer(vertices, 12, 3);
        Buffer* cBuf = new Buffer(colors, 16, 4);

        m_VAO->addBuffer(vBuf, 0);
        m_VAO->addBuffer(cBuf, 1);

        delete vBuf, cBuf;
    }
    Object2D::~Object2D()
    {
        delete m_VAO;
        delete m_EBO;
    }
    void Object2D::setDefaultUV()
    {
        m_UV[0] = glm::vec2(0.0, 0.0);
        m_UV[1] = glm::vec2(0.0, 1.0);
        m_UV[2] = glm::vec2(1.0, 1.0);
        m_UV[3] = glm::vec2(1.0, 0.0);
    }
}
