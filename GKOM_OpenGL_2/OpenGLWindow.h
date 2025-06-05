#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Program.h"
#include "Utilities.h"
#include "Gui.h"

class Camera;

class OpenGLWindow
{
public:

	OpenGLWindow();
	~OpenGLWindow();

	bool InitWindow();

	void InitGui();

	void InitScene();

	void MainLoop();

	void updateDeltaTime();
	void toggleVsync();

	Camera* getCamera();
	Gui* getGui();

private:

	void processInput();

	GLFWwindow* _window;
	std::unique_ptr<Camera> _camera;
	std::unique_ptr<Gui> _gui;

	Program explosionProgram;
	Program staticProgram;

	float _deltaTime;
	bool _vsyncEnabled;

	Explosion _explosion;

	glm::vec2 _windowResolution;
	float _fieldOfView;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;

};
