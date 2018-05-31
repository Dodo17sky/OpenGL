#include "rectangle.h"

namespace Pencil {
    Rectangle::Rectangle(const glm::vec3 & pos, const glm::vec2 & size, Shader * shader, glm::vec4 & color):
        Object2D(pos, size, shader, color),
        m_FillType(RectangleType::RECTYPE_FILLED),
        m_LineWidth(1.0)
    {
        m_Name = "N/A";

        m_Left   = pos.x;
        m_Right  = pos.x + size.x;
        m_Bottom = pos.y;
        m_Top    = pos.y + size.y;

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
        else {
            glLineWidth(m_LineWidth);
            glDrawElements(GL_LINE_LOOP, m_EBO->getCount(), GL_UNSIGNED_SHORT, nullptr);
            glLineWidth(1.0);
        }

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

    glm::vec4 Rectangle::getRectangle() const
    {
        return glm::vec4(
            m_Left, m_Right, m_Bottom, m_Top
        );
    }

    void Rectangle::createFilledRectangle()
    {
        delete m_VAO;
        delete m_EBO;

        GLfloat vertices[] = {
            m_Left,     m_Bottom,   m_Position.z+0.0f,
            m_Left,     m_Top,      m_Position.z+0.0f,
            m_Right,    m_Top,      m_Position.z+0.0f,
            m_Right,    m_Bottom,   m_Position.z+0.0f
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
        
        GLuint bufCount = m_LineWidth * 4;
        GLfloat* ver = new GLfloat[bufCount];


        GLfloat vertices[] = {
            m_Left,  m_Bottom,
            m_Right, m_Bottom,
            m_Right, m_Top,
            m_Left, m_Top
        };

        GLfloat colors[] = {
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
            m_Color.r, m_Color.g, m_Color.b, m_Color.a,
            m_Color.r, m_Color.g, m_Color.b, m_Color.a
        };

        GLushort indices[] = { 0, 1, 1, 2, 2, 3 };

        m_VAO = new VertexArray();
        m_EBO = new IndexBuffer(indices, 6);

        Buffer* vBuf = new Buffer(vertices, 8, 2);
        Buffer* cBuf = new Buffer(colors, 16, 4);

        m_VAO->addBuffer(vBuf, 0);
        m_VAO->addBuffer(cBuf, 1);

        delete[] ver;
        delete cBuf, vBuf;
    }
}