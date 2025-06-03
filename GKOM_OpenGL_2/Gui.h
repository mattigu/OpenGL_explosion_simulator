#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glm/glm.hpp>

#include "Explosion.h"
// Simple wrapper class for ImGui

class Gui 
{
public:
	Gui(GLFWwindow* window);
	~Gui();
	void initImGui() const ;
	void startNewFrame() const;
	void renderGui() const;
	void createExplosionControlWindow(Explosion& explosion) const;
	void createPerformanceOverlay(int triangleCount) const;
	bool wantCaptureMouse() const;

private:
	GLFWwindow* _window;
};