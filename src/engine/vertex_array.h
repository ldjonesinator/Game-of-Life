#pragma once

#include "engine/vertex_buffer.h"
#include "engine/vertex_buffer_layout.h"

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const { glBindVertexArray(m_RendererID); }
	void Unbind() const { glBindVertexArray(0); }
};
