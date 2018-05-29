#pragma once

#include "glm\glm.hpp"
#include "../textures/texture.h"

namespace Pencil {

    class Object {
    protected:
        glm::vec3   m_Position;
        glm::vec2   m_Size;
        glm::vec4   m_Color;
        glm::vec2   m_UV[4];
        Texture*    m_Texture;
    protected:
        Object();
    public:
        Object(const glm::vec3& pos, const glm::vec2& size, glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
    private:
        void setDefaultUV();
    };
}
