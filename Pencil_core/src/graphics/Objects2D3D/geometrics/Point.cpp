#include "Point.h"

namespace Pencil {

    int Point::m_count = 0;

    Point::Point():
        Object2D(glm::vec3(), glm::vec2(), nullptr)
    {
        std::string name = "def_point_" + std::to_string(m_count);
        setName(name);
        m_count++;
    }

    Point::Point(const glm::vec3 & pos, Shader * shader, glm::vec4 & color):
        Object2D(pos, glm::vec2(1, 1), shader, color)
    {
        m_Position = pos;
        m_Name = "N/A";

        createPoint();
    }

    Point::~Point()
    {
    }

    void Point::draw()
    {
        m_Shader->enable();
        m_VAO->bind();
        m_EBO->bind();

        glPointSize(m_PointSize);
        glDrawElements(GL_POINTS, m_EBO->getCount(), GL_UNSIGNED_SHORT, nullptr);
        glPointSize(1.0);

        m_Shader->disable();
        m_VAO->unbind();
        m_EBO->unbind();
    }

    void Point::createPoint()
    {
        delete m_VAO;
        delete m_EBO;

        GLfloat vertices[] = {
            m_Position.x,  m_Position.y,  0.0f
        };

        GLfloat colors[] = {
            m_Color.r, m_Color.g, m_Color.b, m_Color.a
        };

        GLushort indices[] = {
            0
        };

        m_VAO = new VertexArray();
        m_EBO = new IndexBuffer(indices, 1);

        Buffer* vBuf = new Buffer(vertices, 3, 3);
        Buffer* cBuf = new Buffer(colors, 4, 4);

        m_VAO->addBuffer(vBuf, 0);
        m_VAO->addBuffer(cBuf, 1);

        delete vBuf, cBuf;
    }
}