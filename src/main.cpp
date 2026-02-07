#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"

#include "tests/test_clear_colour.h"
#include "tests/test_square.h"


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
	std::cout << "\nVersion: " << glGetString(GL_VERSION) << "\n" << std::endl;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glfwSwapInterval(1);
	glfwSwapBuffers(window);



	{ // KEEPS THE objects out of scope

		Renderer renderer;

		// ImGui initialisation
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui::StyleColorsLight();
		ImGui_ImplOpenGL3_Init();

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColour>("Test Clear Colour");
		testMenu->RegisterTest<test::TestSquare>("Test Square");


		// main loop
		while (!glfwWindowShouldClose(window)) {
			glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		    renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
		    ImGui_ImplGlfw_NewFrame();
		    ImGui::NewFrame();

		    if (currentTest) {
		    	currentTest->OnUpdate(0.0f);
		    	currentTest->OnRender();
		    	ImGui::Begin("Test");
		    	if (currentTest != testMenu && ImGui::Button("<-")) {
		    		delete currentTest;
		    		currentTest = testMenu;
		    	}
		    	currentTest->OnImGuiRender();
		    	ImGui::End();
		    }


			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		    glfwSwapBuffers(window);

		    glfwPollEvents();
		}

		delete currentTest;
		if (currentTest != testMenu) {
			delete testMenu;
		}
	}

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
