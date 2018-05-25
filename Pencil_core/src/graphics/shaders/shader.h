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

        void setUniform4f(const char* name, float f1, float f2, float f3, float f4);

    private:
        unsigned int compileShader(GLenum type, const char* filePath);
        int getUniformLocation(const char* name);
    };
}
