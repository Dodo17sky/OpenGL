#pragma once

#include <deque>

#include "Object2D.h"

namespace Pencil {

    class Renderer {
    private:
        std::deque<Object2D*> m_ObjectsList;

    public:
        void add(Object2D* obj);
        void draw();
    };
}
