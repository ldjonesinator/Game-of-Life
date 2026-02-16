#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size, bool isDynamic);
	~VertexBuffer();

	void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
	void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
};
