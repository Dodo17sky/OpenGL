#pragma once

#include "../Object2D.h"

namespace Pencil {

    class Rectangle: public Object2D {
    public:
        enum RectangleType { RECTYPE_UNKNOWN, RECTYPE_FILLED, RECTYPE_EMPTY };
    private:
        RectangleType m_FillType;
        GLushort m_LineThickness;
    public:
        Rectangle(const glm::vec3& pos, const glm::vec2& size, Shader* shader = nullptr, glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
        ~Rectangle();

        void draw() override;

        void setFillType(Rectangle::RectangleType fillType);
    private:
        void createFilledRectangle();
        void createEmptyRectangle();
    };
}
