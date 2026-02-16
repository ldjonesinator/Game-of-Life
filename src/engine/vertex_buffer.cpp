#include "engine/vertex_buffer.h"
#include "engine/vertex_buffer_layout.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, bool isDynamic)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	if (isDynamic) {
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

	} else {
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}
