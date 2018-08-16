#pragma once

#include "../Object2D.h"

#include <string>

namespace Pencil {

    class Point: public Object2D {
        static int m_count;
        GLfloat m_PointSize;
    public:
        Point();
        Point(const glm::vec3& pos, Shader* shader = nullptr, glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
        ~Point();

        void draw() override;

        inline void setPointSize(GLfloat size) { m_PointSize = size; }
        inline void setName(const std::string& name) { m_Name = name; }

    private:
        void createPoint();
    };
}
