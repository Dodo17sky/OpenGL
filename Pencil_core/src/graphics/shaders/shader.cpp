#include "shader.h"

#include <iostream>

#include "../../utils/fileutils.h"

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

namespace Pencil {

    Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
    {
        unsigned int vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShaderPath);
        unsigned int fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

        m_programId = glCreateProgram();
        glAttachShader(m_programId, vertexShaderId);
        glAttachShader(m_programId, fragmentShaderId);
        glLinkProgram(m_programId);

        int ok;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &ok);
        if (!ok) {
            char infoLog[512];
            glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
            std::cout << "Shader error: Program linking failed !\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_programId);
    }

    void Shader::enable() const
    {
        glUseProgram(m_programId);
    }

    void Shader::disable() const
    {
        glUseProgram(0);
    }

    void Shader::setUniform4f(const GLchar * name, float r, float g, float b)
    {
        GLint id = glGetUniformLocation(m_programId, name);
        glUniform4f(id, r, g, b, 1.0);
    }

    unsigned int Shader::compileShader(GLenum type, const char* filePath)
    {
        std::string str = Pencil::read_file(filePath);
        const char* shaderSource = str.c_str();
        unsigned int shaderId;

        shaderId = glCreateShader(type);
        glShaderSource(shaderId, 1, &shaderSource, NULL);
        glCompileShader(shaderId);
        int ok;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            char infoLog[512];
            glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
            std::cout << "Shader error: " << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment")
                << " compilation failed !\n" << infoLog << std::endl;
        }

        return shaderId;
    }

}
