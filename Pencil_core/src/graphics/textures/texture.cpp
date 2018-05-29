#include "texture.h"
#include "../../../ext/stb_image/stb_image.h"

#include <iostream>

namespace Pencil {
    GLushort Texture::m_TexIndex = 0;

	Texture::Texture(const std::string & fileName)
		: m_FileName(fileName)
	{
		GLint maxTex;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTex);
		if (m_TexIndex >= maxTex) {
			std::cout << "Warning: maxim textures image units loaded. Can not create new texture." << std::endl;
			return;
		}
		m_TextureSlot = GL_TEXTURE0 + m_TexIndex;
		m_TexIndex++;

		m_TextureId = load();
	}

	Texture::~Texture()
	{
	}

	void Texture::bind()
	{
		glActiveTexture((GLenum)m_TextureSlot);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);
	}

	void Texture::unbind()
	{
		glActiveTexture((GLenum)m_TextureSlot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint Texture::load()
	{
		GLuint texId;
		unsigned char* buffer;

        stbi_set_flip_vertically_on_load(true);
		buffer = stbi_load(m_FileName.c_str(), &m_Width, &m_Height, &m_NmbChannels, 0);
		glGenTextures(1, &texId);
		glActiveTexture((GLenum)m_TextureSlot);
		glBindTexture(GL_TEXTURE_2D, texId);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (buffer) {
			GLenum format = (m_NmbChannels == 3) ? GL_RGB : GL_RGBA;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, buffer);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load image texture: " << m_FileName << std::endl;
		}
		stbi_image_free(buffer);

		return texId;
	}
}