#include "Gui.h"

Gui::Gui(GLFWwindow* window) : _window (window) {}


Gui::~Gui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Gui::initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext(); 
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Gui::startNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::renderGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::createExplosionControlWindow(float* explosionSpeed, glm::vec3* explosionOrigin, bool* explosionPaused)
{
	ImGui::Begin("Explosion effects");

	ImGui::SliderFloat("Speed", explosionSpeed, -10.f, 10.f);

	if (ImGui::Button(*explosionPaused ? "Resume" : "Pause")) {
		*explosionPaused = !(*explosionPaused);
	};


	ImGui::Text("Explosion Origin");
	ImGui::DragFloat("X", &explosionOrigin->x, 0.1f, -20.0f, 20.0f);
	ImGui::DragFloat("Y", &explosionOrigin->y, 0.1f, -20.0f, 20.0f);
	ImGui::DragFloat("Z", &explosionOrigin->z, 0.1f, -20.0f, 20.0f);
	

	ImGui::End();
}

bool Gui::wantCaptureMouse()
{
	return ImGui::GetIO().WantCaptureMouse;
}