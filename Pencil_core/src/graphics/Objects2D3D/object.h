#pragma once

#include "glm\glm.hpp"

#include "../buffers/vertexarray.h"
#include "../buffers/indexbuffer.h"
#include "../buffers/buffer.h"
#include "../textures/texture.h"
#include "../shaders/shader.h"

namespace Pencil {

    class Object {
    protected:
        glm::vec3   m_Position;
        glm::vec2   m_Size;
        glm::vec4   m_Color;
        glm::vec2   m_UV[4];

        VertexArray* m_VAO;
        IndexBuffer* m_EBO;
        Texture*    m_Texture;
        Shader*     m_Shader;
    protected:
        Object();
    public:
        Object(const glm::vec3& pos, const glm::vec2& size, glm::vec4& color = glm::vec4(1.0, 1.0, 1.0, 1.0));
        ~Object();

        inline const VertexArray* getVAO() const { return m_VAO; }
        inline const IndexBuffer* getEBO() const { return m_EBO; }
        inline Shader* getShader() const { return m_Shader; }

        inline const glm::vec3& getPosition() const { return m_Position; }
        inline const glm::vec2& getSize() const { return m_Size; }
        inline const glm::vec4& getColor() const { return m_Color; }

    private:
        void setDefaultUV();
    };
}
