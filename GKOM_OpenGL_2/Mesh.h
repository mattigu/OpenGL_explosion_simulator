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

class Mesh {
protected:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture diffuseTexture)
		: _vertices(std::move(vertices)), 
		_indices(std::move(indices)), 
		_diffuseTexture(std::move(diffuseTexture)) {};

	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	Texture _diffuseTexture;

	GLuint VBO = 0, EBO = 0, VAO = 0;

public:
	virtual void setupMesh() = 0;
	virtual void Draw(Program& program) const = 0;
};

// Hold 1 modelMatrix, which the model can apply new tranformations to. Render using the modelMatrix by default. 
// Maybe separate function to draw with a custom one?