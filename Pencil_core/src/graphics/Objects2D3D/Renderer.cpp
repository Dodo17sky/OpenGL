#include "Renderer.h"

#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include <iostream>

namespace Pencil {
    void Renderer::add(Object2D * obj)
    {
        m_ObjectsList.push_back(obj);
    }

    void Renderer::draw()
    {
        while(!m_ObjectsList.empty())
        {
            Object2D* object = m_ObjectsList.front();

            if (object->isRendereble()) {
                object->draw();
            }
            else {
                std::cout << "Warning: Object2D cound not be rendered" << std::endl;
            }
            m_ObjectsList.pop_front();
        }
    }
}
