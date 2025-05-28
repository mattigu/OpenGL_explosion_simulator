#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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
private:
	void setupMesh();
protected:
	virtual ~Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture diffuseTexture)
		: _vertices(std::move(vertices)), 
		_indices(std::move(indices)), 
		_diffuseTexture(std::move(diffuseTexture)) {
		setupMesh();
	};

	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	Texture _diffuseTexture;

	GLuint _VBO = 0, _EBO = 0, _VAO = 0;

public:
	virtual void Draw(Program& program) const = 0;
	virtual void applyTransformation(const glm::mat4& transform) = 0;
};