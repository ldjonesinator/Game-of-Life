#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "GOL.h"

#include "engine/window.h"
#include "engine/timestep.h"

#include "engine/renderer.h"
#include "engine/vertex_buffer.h"
#include "engine/index_buffer.h"
#include "engine/vertex_array.h"
#include "engine/shader.h"




int main()
{
	Window window(0);

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

		GOL game(&window);

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

			

			game.OnUpdate(timestep);

			ImGui::SetNextWindowSize(ImVec2(350, 180), ImGuiCond_Once);
			ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
			ImGui::Begin("Tools");
			game.OnImGuiRender();

			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 80) / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 25);

			if (ImGui::Button("Fullscreen")) {
				window.ToggleFullscreen();
			}

			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		    glfwSwapBuffers(window.GetWindow());

		    glfwPollEvents();
		}
	}

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	return 0;
}
