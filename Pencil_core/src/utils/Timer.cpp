#include "Timer.h"
#include <iostream>

namespace Pencil {
    Timer::Timer()
    {
        m_lastFPS = glfwGetTime();
        frames = 0;
    }

    void Timer::startCount()
    {
        m_startTime = glfwGetTime();
    }

	bool Timer::passed(float seconds)
	{
		if (glfwGetTime() > (m_startTime + seconds))
			return true;
		else
			return false;
	}

    float Timer::getElapsedTime()
    {
        return (glfwGetTime() - m_startTime);
    }
    void Timer::printFPS()
    {
        frames++;
        float now = glfwGetTime();

        if ( now >= m_lastFPS+1.0f ) {
            std::cout << "FPS = " << frames << std::endl;
            frames = 0;
            m_lastFPS = now;
        }
    }
}
