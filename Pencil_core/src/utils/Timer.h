#pragma once

#include "GLFW\glfw3.h"

namespace Pencil {

    class Timer {
    private:
        float m_startTime;
        float m_lastFPS;
        unsigned int frames;
    public:
        Timer();
        inline void startCount();
        inline float getElapsedTime() const;
        void printFPS();
        inline float now() { return glfwGetTime(); }
    };
}
