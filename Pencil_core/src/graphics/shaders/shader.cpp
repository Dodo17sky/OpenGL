#include "shader.h"

#include <iostream>

#include "../../utils/fileutils.h"
#include "glad\glad.h"

namespace Pencil {

    Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
    {
        std::string vertexStr = Pencil::read_file(vertexShaderPath);
        std::string fragmentStr = Pencil::read_file(fragmentShaderPath);

        const char* vertexSource = vertexStr.c_str();
        const char* fragmentSource = fragmentStr.c_str();

        unsigned int vertexShaderId;
        unsigned int fragmentShaderId;

        vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderId, 1, &vertexSource, NULL);
        glCompileShader(vertexShaderId);

    }

}
