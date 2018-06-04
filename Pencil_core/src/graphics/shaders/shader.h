#pragma once

#include <string>
#include "glm\glm.hpp"

namespace Pencil {

    class Shader {
    private:
        unsigned int m_programId;
    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();
        void enable() const;
        void disable() const;
		inline unsigned int getID() const { return m_programId; }

		void setUniformMatrix4f(const char* name, const float* matrix);
        void setUniform4f(const char* name, float f1, float f2, float f3, float f4);
        void setUniform1f(const char* name, float f1);
		void setUniform1i(const char* name, int i1);

    private:
        unsigned int compileShader(int type, const char* filePath);
        int getUniformLocation(const char* name);
    };
}
