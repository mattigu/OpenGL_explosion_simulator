#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Program.h"
#include "Utilities.h"

class Camera;

class OpenGLWindow
{
public:

	OpenGLWindow();
	~OpenGLWindow();

	bool InitWindow();

	void InitScene();

	void MainLoop();

private:

	void processInput();

	GLFWwindow* _window;
	std::unique_ptr<Camera> _camera;

	Program transformationProgram;

	GLuint objectVAO;
	GLenum objectVAOPrimitive;
	unsigned int objectVAOVertexCount;

	glm::vec2 windowResolution;
	float fieldOfView;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 modelMatrix;

};
