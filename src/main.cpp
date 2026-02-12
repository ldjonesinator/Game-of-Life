#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "window.h"
#include "timestep.h"

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"

#include "tests/test_clear_colour.h"
#include "tests/test_square.h"
#include "tests/test_square_batch.h"
#include "tests/test_GOL.h"


int main()
{
	Window window;

	if (!window.IsValid()) {
        std::cerr << "Window initialization failed." << std::endl;
        return -1;
	} else {

		Renderer renderer;

		// ImGui initialisation
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
		ImGui::StyleColorsLight();
		ImGui_ImplOpenGL3_Init();

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColour>("Test Clear Colour");
		testMenu->RegisterTest<test::TestSquare>("Test Square");
		testMenu->RegisterTest<test::TestSquareBatch>("Test Batch Squares");
		testMenu->RegisterTest<test::TestGOL>("John Conway's Game of Life", &window);

		float m_LastFrameTime = 0.0f;

		// main loop
		while (!glfwWindowShouldClose(window.GetWindow())) {

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		    renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
		    ImGui_ImplGlfw_NewFrame();
		    ImGui::NewFrame();

		    if (currentTest) {
		    	currentTest->OnUpdate(timestep);

		    	ImGui::SetNextWindowSize(ImVec2(350, 200), ImGuiCond_Once);
				ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
		    	ImGui::Begin("Tools");

		    	if (currentTest != testMenu && ImGui::Button("<-")) {
		    		delete currentTest;
		    		currentTest = testMenu;
		    	}

		    	currentTest->OnImGuiRender();

				ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 80) / 2);
				ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 25);

				if (ImGui::Button("Fullscreen")) {
					window.ToggleFullscreen();
				}

		    	ImGui::End();
		    }


			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		    glfwSwapBuffers(window.GetWindow());

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

	return 0;
}
