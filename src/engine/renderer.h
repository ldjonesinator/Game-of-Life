#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/vertex_array.h"
#include "engine/index_buffer.h"
#include "engine/shader.h"

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};
