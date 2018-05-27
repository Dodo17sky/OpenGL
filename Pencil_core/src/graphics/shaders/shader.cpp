#include "shader.h"

#include <iostream>

#include "../../utils/fileutils.h"

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

	void Shader::setUniformMatrix4f(const char * name, const GLfloat* matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix);
	}

	void Shader::setUniform4f(const char * name, float f1, float f2, float f3, float f4)
    {
        glUniform4f(getUniformLocation(name), f1, f2, f3, f4);
    }

    void Shader::setUniform1f(const char * name, float f1)
    {
        glUniform1f(getUniformLocation(name), f1);
    }

	void Shader::setUniform1i(const char * name, int i1)
	{
		glUniform1i(getUniformLocation(name), i1);
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
			system("pause");
			glDeleteShader(shaderId);
			exit(-1);
        }

        return shaderId;
    }

    int Shader::getUniformLocation(const char * name)
    {
        int uniformId = glGetUniformLocation(m_programId, name);
        if(uniformId == (-1))
            std::cout << "Error: Uniform \"" << name << "\" not found" << std::endl;
        return uniformId;
    }

}
