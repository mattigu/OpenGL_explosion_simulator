#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glm/glm.hpp>

// Simple wrapper class for ImGui

class Gui 
{
public:
	Gui(GLFWwindow* window);
	~Gui();
	void initImGui();
	void startNewFrame();
	void renderGui();
	void createExplosionControlWindow(float* explosionSpeed, float* explosionTime, glm::vec3* explosionOrigin, bool* explosionPaused);

	bool wantCaptureMouse();

private:
	GLFWwindow* _window;
};