#pragma once

#include "../Object2D.h"

#include <string>
#include <vector>

namespace Pencil {

    class Point: public Object2D {
        static int              m_count;
        GLfloat                 m_PointSize;
        unsigned int            m_PointsCount;
        std::vector<glm::vec3>  m_Points;
    public:
        Point(Shader* shader = nullptr);
        ~Point();

        void draw() override;
        void addPoints(const glm::vec3 *data, unsigned int count);
        
        inline void setPointSize(GLfloat size) { m_PointSize = size; }
        inline void setName(const std::string& name) { m_Name = name; }

    private:
        void createPoint();
    };
}
