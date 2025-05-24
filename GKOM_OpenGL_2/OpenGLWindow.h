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

	Program transformationProgram;
	Program staticProgram;

	float _deltaTime;
	bool _vsyncEnabled;

	float explosionTime;
	float explosionSpeed;
	bool explosionPaused;
	glm::vec3 explosionOrigin;

	GLuint objectVAO;
	GLenum objectVAOPrimitive;
	unsigned int objectVAOVertexCount;

	glm::vec2 windowResolution;
	float fieldOfView;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 modelMatrix;

};
