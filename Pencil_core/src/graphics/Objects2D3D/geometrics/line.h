#pragma once

#include "../Object2D.h"

#include <string>

namespace Pencil {

    class Line: public Object2D {
        glm::vec3 m_Start;
        glm::vec2 m_End;
        GLfloat m_LineWidth;
    public:
        Line(const glm::vec3& start, const glm::vec2& end, Shader* shader = nullptr, glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
        ~Line();

        void draw() override;

        inline void setLineWidth(GLfloat width) { m_LineWidth = width; }
        inline void setName(const std::string& name) { m_Name = name; }

    private:
        void createLine();
    };
}
