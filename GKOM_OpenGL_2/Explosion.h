#pragma once

#include <glm/glm.hpp>

struct Explosion {
	// Shader params
	glm::vec3 explosionOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
	float explosionTime = 0.0f;
	float explosionStrength = 10.0f;
	float explosionSpeed = 10.0f;

	// Outside control
	bool paused = false;
	float simulationSpeed = 1.0;

	bool togglePause();
	void updateTime(float deltaTime);
};