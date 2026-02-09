#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <csignal>

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
#include "tests/test_square_batch.h"
#include "tests/test_GOL.h"


const unsigned int WINDOW_WIDTH = 1600;
const unsigned int WINDOW_HEIGHT = 900;



void APIENTRY GLDebugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    // Ignore non-significant notification spam
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        return;

    std::cerr << "\n--- OpenGL Debug Message ---\n";
    std::cerr << "Message: " << message << "\n";

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            std::cerr << "Type: ERROR\n";
            if (type == GL_DEBUG_TYPE_ERROR) {
					#ifdef _MSC_VER
					__debugbreak();
					#else
					raise(SIGTRAP);
					#endif
				}
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cerr << "Type: UNDEFINED BEHAVIOR\n";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cerr << "Type: PERFORMANCE\n";
            break;
        default:
            std::cerr << "Type: OTHER\n";
            break;
    }

    std::cerr << "---------------------------\n";
}


int main()
{
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "John Conway's Game of Life", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(GLDebugCallback, nullptr);
		glDebugMessageControl(
		    GL_DONT_CARE,
		    GL_DONT_CARE,
		    GL_DONT_CARE,
		    0, nullptr,
		    GL_TRUE
		);
	}

	std::cout << "\nVersion: " << glGetString(GL_VERSION) << "\n" << std::endl;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glfwSwapInterval(2);
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
		testMenu->RegisterTest<test::TestSquareBatch>("Test Batch Squares");
		testMenu->RegisterTest<test::TestGOL>("John Conway's Game of Life");


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

		    	ImGui::SetNextWindowSize(ImVec2(350, 150), ImGuiCond_Once);
				ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
		    	ImGui::Begin("Programs");

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
