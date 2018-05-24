#pragma once

#include <string>

namespace Pencil {

    class Shader {
    private:
        unsigned int m_shaderId;
    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    };
}
