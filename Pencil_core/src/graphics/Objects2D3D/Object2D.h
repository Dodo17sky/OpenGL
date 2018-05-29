#pragma once

#include "object.h"

namespace Pencil {

    class Object2D : public Object {
    private:
        
    public:
        Object2D(const glm::vec3& pos, const glm::vec2& size, Shader* shader, glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
        ~Object2D();

    };
}
