#pragma once

#include "../Object2D.h"

#include <string>

namespace Pencil {

    class Rectangle: public Object2D {
    public:
        enum RectangleType { RECTYPE_UNKNOWN, RECTYPE_FILLED, RECTYPE_EMPTY };
    private:
        GLfloat m_Left;
        GLfloat m_Right;
        GLfloat m_Top;
        GLfloat m_Bottom;
        RectangleType m_FillType;
        GLfloat m_LineWidth;
    public:
        Rectangle(const glm::vec3& pos, const glm::vec2& size, Shader* shader = nullptr, glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
        ~Rectangle();

        void draw() override;

        void setFillType(Rectangle::RectangleType fillType);
        inline void setLineWidth(GLfloat width) { m_LineWidth = width; }
        inline void setName(const std::string& name) { m_Name = name; }

        glm::vec4 getRectangle() const;
    private:
        void createFilledRectangle();
        void createEmptyRectangle();
    };
}
