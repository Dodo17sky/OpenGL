#include "Renderer.h"

#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

namespace Pencil {
    void Renderer::add(const Object2D * obj)
    {
        m_ObjectsList.push_back(obj);
    }

    void Renderer::draw()
    {
        while(!m_ObjectsList.empty())
        {
            const Object2D* object = m_ObjectsList.front();
            object->getShader()->enable();
            object->getVAO()->bind();
            object->getEBO()->bind();
            
            glDrawElements(GL_TRIANGLES, object->getEBO()->getCount(),GL_UNSIGNED_SHORT, nullptr);
                
            object->getEBO()->unbind();
            object->getVAO()->unbind();
            object->getShader()->disable();

            m_ObjectsList.pop_front();
        }
    }
}
