#pragma once

#include <vector>
#include "glad\glad.h"
#include "buffer.h"

namespace Pencil {

	class VertexArray
	{
	private:
		GLuint m_ArrayID;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer* buffer, GLuint index);
		void bind() const;
		void unbind() const;
	};

}