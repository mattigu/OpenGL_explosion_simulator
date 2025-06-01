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

void Gui::createExplosionControlWindow(float* explosionSpeed, float* explosionTime, glm::vec3* explosionOrigin, bool* explosionPaused, float* explosionStrength) const
{
	ImGui::Begin("Explosion effects");

	ImGui::SliderFloat("Speed", explosionSpeed, -10.f, 10.f);

	if (ImGui::Button(*explosionPaused ? "Resume" : "Pause")) {
		*explosionPaused = !(*explosionPaused);
	};

	if (ImGui::Button("Reset")) {
		*explosionTime = 0;
	};


	ImGui::Text("Explosion Origin");
	ImGui::DragFloat("X", &explosionOrigin->x, 0.1f, -20.0f, 20.0f);
	ImGui::DragFloat("Y", &explosionOrigin->y, 0.1f, -20.0f, 20.0f);
	ImGui::DragFloat("Z", &explosionOrigin->z, 0.1f, -20.0f, 20.0f);
	ImGui::Text("Explosion Strength");
	ImGui::SliderFloat("Strength", explosionStrength, 0.0f, 50.0f);
	
	ImGui::End();
}

void Gui::createPerformanceOverlay() const
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

	ImGui::End();
}

bool Gui::wantCaptureMouse() const
{
	return ImGui::GetIO().WantCaptureMouse;
}