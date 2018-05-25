#pragma once

#include <string>
#include "glad\glad.h"

namespace Pencil {

    class Shader {
    private:
        unsigned int m_programId;
    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();
        void enable() const;
        void disable() const;

        void setUniform4f(const GLchar* name, float r, float g, float b);

    private:
        unsigned int compileShader(GLenum type, const char* filePath);
    };
}
