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
        void startCount();
		bool passed(float seconds);
        float getElapsedTime();
        void printFPS();
        inline float now() { return glfwGetTime(); }
    };
}
