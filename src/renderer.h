#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};
