#include "line.h"

namespace Pencil {
    Line::Line(const glm::vec3 & start, const glm::vec2 & end, Shader * shader, glm::vec4 & color):
        Object2D(start, glm::vec2(end.x-start.x, end.y-start.y), shader, color)
        , m_Start(start)
        , m_End(end)
        , m_LineWidth(1.0)
    {
        m_Name = "N/A";

        createLine();
    }

    Line::~Line()
    {
    }

    void Line::draw()
    {
        m_Shader->enable();
        m_VAO->bind();
        m_EBO->bind();

        glLineWidth(m_LineWidth);
        glDrawElements(GL_LINES, m_EBO->getCount(), GL_UNSIGNED_SHORT, nullptr);
        glLineWidth(1.0);

        m_Shader->disable();
        m_VAO->unbind();
        m_EBO->unbind();
    }

    void Line::createLine()
    {
        delete m_VAO;
        delete m_EBO;

        GLfloat vertices[] = {
            m_Start.x,  m_Start.y,  0.0f,
            m_End.x  ,  m_End.y  ,  0.0f
        };

        GLfloat colors[] = {
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
        };

        GLushort indices[] = {
            0, 1
        };

        m_VAO = new VertexArray();
        m_EBO = new IndexBuffer(indices, 2);

        Buffer* vBuf = new Buffer(vertices, 6, 3);
        Buffer* cBuf = new Buffer(colors, 8, 4);

        m_VAO->addBuffer(vBuf, 0);
        m_VAO->addBuffer(cBuf, 1);

        delete vBuf, cBuf;
    }
}