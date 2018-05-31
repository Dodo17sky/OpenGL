#pragma once

#include <deque>

#include "Object2D.h"

namespace Pencil {

    class Renderer {
    private:
        std::deque<const Object2D*> m_ObjectsList;

    public:
        void add(const Object2D* obj);
        void draw();
    };
}
