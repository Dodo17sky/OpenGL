#pragma once

#include <deque>

#include "Object2D.h"

namespace Pencil {

    class Renderer {
    private:
        std::deque<Object2D*> m_ObjectsList;

    public:
        ~Renderer();
        void add(Object2D* obj);
        void draw();

        const Object2D* getIntersectedObject(double x, double y) const;
    };
}
