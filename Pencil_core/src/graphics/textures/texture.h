#pragma once

#include "glad\glad.h"

#include <string>

namespace Pencil {

#define TEXTURE_SLOT(index)		GL_TEXTURE#index

	class Texture {
	private:
		static GLushort m_TexIndex;
        GLushort m_TextureSlot;
		GLuint m_TextureId;
		GLsizei m_Width, m_Height, m_NmbChannels;
		std::string m_FileName;
	public:
		Texture(const std::string& fileName);
		~Texture();

		void bind();
		void unbind();

		inline const GLuint getID() const { return m_TextureId;  }
		inline const GLushort getTextureSlot() const { return (m_TextureSlot - GL_TEXTURE0); }
		inline const GLsizei getWidth() const { return m_Width;  }
		inline const GLsizei getHeight() const { return m_Height;  }

	private:
		GLuint load();
	};
}
