#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"


const unsigned int WINDOW_WIDTH = 1600;
const unsigned int WINDOW_HEIGHT = 900;


int main()
{
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "John Conway's Game of Life", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();
	//    std::cout << glGetString(GL_VERSION) << std::endl;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glfwSwapInterval(1);

	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	float positions[] = {
		-0.15f, -0.25f,
		0.15f, -0.25f,
		0.15f, 0.25f,
		-0.15f, 0.25f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	{
		VertexArray va;
		VertexBuffer vb(positions, 2 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);


		Shader shader("resources/shaders/Basic.shader");
		shader.Bind();

		shader.SetUniform4f("u_Color", 0.92f, 0.68f, 0.20f, 1.0f);


		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		float r = 0.0f;
		float increment = 0.01f;

		// main loop
		while (!glfwWindowShouldClose(window)) {

		    glClear(GL_COLOR_BUFFER_BIT);

		    shader.Bind();
		    shader.SetUniform4f("u_Color", r, 0.68f, 0.20f, 1.0f);

		    if (r > 1.0f) {
		        increment = -0.01f;
		    } else if (r < 0.0f) {
		        increment = 0.01f;
		    }
		    r += increment;

		    va.Bind();
		    ib.Bind();

		    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		    glfwSwapBuffers(window);

		    glfwPollEvents();
		}
	} // KEEPS THE objects out of scope

	//    glDeleteProgram(shader);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
