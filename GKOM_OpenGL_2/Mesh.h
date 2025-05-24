#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec4 Color;
	glm::vec2 TexCoords;
};

// A mesh with instancing requires a different setup

class Mesh {
protected:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		: _vertices(vertices), _indices(indices) {};

	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;

public:
	virtual void setupMesh() = 0;
	virtual void Draw() = 0;
};