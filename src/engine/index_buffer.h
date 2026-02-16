#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
	void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	inline unsigned int GetCount() const { return m_Count; }
};
