#include "Renderer.h"

#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "geometrics\rectangle.h"

#include <iostream>

namespace Pencil {
    Renderer::~Renderer()
    {
    }

    void Renderer::add(Object2D * obj)
    {
        m_ObjectsList.push_back(obj);
    }

    void Renderer::draw()
    {
        for each (Object2D* object in m_ObjectsList)
        {
            if (object->isRendereble()) {
                object->draw();
            }
            else {
                std::cout << "Warning: Object2D cound not be rendered" << std::endl;
            }
            //m_ObjectsList.pop_front();
        }
    }

    const Object2D * Renderer::getIntersectedObject(double x, double y) const
    {
        for each (Object2D* var in m_ObjectsList)
        {
            Pencil::Rectangle* r = (Pencil::Rectangle*) var;
            glm::vec4 limit = r->getRectangle();
            if( limit.y > x && x > limit.x && limit.w > y && limit.z < y)
                return var;
        }
        return nullptr;
    }
}
