#include "Object2D.h"

namespace Pencil {
    Object2D::Object2D(const glm::vec3& pos, const glm::vec2& size, Shader* shader, glm::vec4& color)
        : Object(pos, size, color)
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
        m_VAO->addBuffer(new Buffer(vertices, 12, 3), 0);
        m_VAO->addBuffer(new Buffer(colors, 16, 4), 1);
        m_EBO = new IndexBuffer(indices, 6);
        m_Shader = shader;
    }
    Object2D::~Object2D()
    {
        delete m_VAO;
        delete m_EBO;
    }
}
