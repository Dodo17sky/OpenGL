#include "rectangle.h"

namespace Pencil {
    Rectangle::Rectangle(const glm::vec3 & pos, const glm::vec2 & size, Shader * shader, glm::vec4 & color):
        Object2D(pos, size, shader, color),
        m_FillType(RectangleType::RECTYPE_FILLED),
        m_LineThickness(1)
    {
        if(m_FillType == RECTYPE_FILLED)
            createFilledRectangle();
        else
            createEmptyRectangle();
    }

    Rectangle::~Rectangle()
    {
    }

    void Rectangle::draw()
    {
        m_Shader->enable();
        m_VAO->bind();
        m_EBO->bind();

        if(m_FillType == RECTYPE_FILLED)
            glDrawElements(GL_TRIANGLES, m_EBO->getCount(), GL_UNSIGNED_SHORT, nullptr);
        else
            glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_SHORT, nullptr);

        m_Shader->disable();
        m_VAO->unbind();
        m_EBO->unbind();
    }

    void Rectangle::setFillType(Rectangle::RectangleType fillType)
    {
        m_FillType = fillType;
        if(m_FillType == RECTYPE_FILLED)
            createFilledRectangle();
        else
            createEmptyRectangle();
    }

    void Rectangle::createFilledRectangle()
    {
        delete m_VAO;
        delete m_EBO;

        GLfloat vertices[] = {
            m_Position.x+0.0f,     m_Position.y+0.0f,     m_Position.z+0.0f,
            m_Position.x+0.0f,     m_Position.y+m_Size.y,   m_Position.z+0.0f,
            m_Position.x+m_Size.x,   m_Position.y+m_Size.y,   m_Position.z+0.0f,
            m_Position.x+m_Size.x,   m_Position.y+0.0f,     m_Position.z+0.0f
        };

        GLfloat colors[] = {
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
            m_Color.r, m_Color.g, m_Color.b, m_Color.a
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

    void Rectangle::createEmptyRectangle()
    {
        delete m_VAO;
        delete m_EBO;

        GLfloat vertices[] = {
            m_Position.x+0.0f, m_Position.y+0.0f,
            m_Position.x+m_Size.x, m_Position.y+0.0f,
            m_Position.x+m_Size.x, m_Position.y+m_Size.y,
            m_Position.x+0.0f, m_Position.y+m_Size.y,
        };

        GLfloat colors[] = {
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
            m_Color.r, m_Color.g, m_Color.b, m_Color.a
        };

        GLushort indices[] = {
            0, 1, 1, 2, 2, 3
        };

        m_VAO = new VertexArray();
        m_EBO = new IndexBuffer(indices, 6);

        Buffer* vBuf = new Buffer(vertices, 8, 2);
        Buffer* cBuf = new Buffer(colors, 16, 4);

        m_VAO->addBuffer(vBuf, 0);
        m_VAO->addBuffer(cBuf, 1);

        delete vBuf, cBuf;
    }
}