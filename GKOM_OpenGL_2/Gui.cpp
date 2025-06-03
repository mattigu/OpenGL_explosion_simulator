#include "Gui.h"

Gui::Gui(GLFWwindow* window) : _window (window) {}


Gui::~Gui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Gui::initImGui() const
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext(); 
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Gui::startNewFrame() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::renderGui() const
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::createExplosionControlWindow(Explosion& e) const
{
	ImGui::Begin("Explosion effects");

	ImGui::Text("Simulation speed");
	ImGui::SliderFloat("##Simulation speed", &e.simulationSpeed, -10.f, 10.f);

	if (ImGui::Button(&e.paused ? "Resume" : "Pause")) {
		e.togglePause();
	};

	if (ImGui::Button("Reset")) {
		e.explosionTime = 0;
	};


	ImGui::Text("Explosion Origin");
	ImGui::DragFloat("X", &e.explosionOrigin.x, 0.1f, -20.0f, 20.0f);
	ImGui::DragFloat("Y", &e.explosionOrigin.y, 0.1f, -20.0f, 20.0f);
	ImGui::DragFloat("Z", &e.explosionOrigin.z, 0.1f, -20.0f, 20.0f);
	ImGui::Text("Explosion Strength");
	ImGui::SliderFloat("Strength", &e.explosionStrength, 0.0f, 50.0f);
	
	ImGui::End();
}

void Gui::createPerformanceOverlay(int triangleCount) const
{
	float fps = ImGui::GetIO().Framerate;
	float frameTime = 1000.0f / fps;

	ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav;

	ImGui::Begin("Performance stats", nullptr, windowFlags);

	ImGui::Text("FPS: %.1f", fps);
	ImGui::Text("Frame Time: %.2f ms", frameTime);
	ImGui::Text("Triangles: %d", triangleCount);

	ImGui::End();
}

bool Gui::wantCaptureMouse() const
{
	return ImGui::GetIO().WantCaptureMouse;
}