#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Program.h"

#include <string>
#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec4 Color;
	glm::vec2 TexCoords;
};


struct Texture {
	GLuint id;
	std::string type;
	std::string path;
};

// A mesh with instancing requires a different setup

// Should probably use std::move to not copy the data. I'll do that once this simple version works
class Mesh {
protected:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Texture& diffuseTexture)
		: _vertices(vertices), _indices(indices), _diffuseTexture(diffuseTexture) {};

	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	Texture _diffuseTexture;

	GLuint VBO = 0, EBO = 0, VAO = 0;

public:
	virtual void setupMesh() = 0;
	virtual void Draw(Program& program) = 0;
};