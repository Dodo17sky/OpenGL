#pragma once

#include <deque>

#include "object.h"

namespace Pencil {

    class Renderer {
    private:
        std::deque<const Object*> m_ObjectsList;

    public:
        void add(const Object* obj);
        void draw();
    };
}
