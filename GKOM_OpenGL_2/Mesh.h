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
	GLuint id = 0;
};

// A mesh with instancing requires a different setup

class Mesh {
private:
	void setupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
protected:
	virtual ~Mesh();
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture diffuseTexture)
		: _diffuseTexture(diffuseTexture), _numIndices(static_cast<GLsizei>(indices.size())) {
		setupMesh(vertices, indices);
	};

	Mesh(GLuint vao, GLuint vbo, GLuint ebo, Texture diffuseTexture, GLsizei numIndices)
		: _VAO(vao), _VBO(vbo), _EBO(ebo), _diffuseTexture(diffuseTexture), _numIndices(numIndices) {};

	GLsizei _numIndices;
	Texture _diffuseTexture;
	GLuint _VBO = 0, _EBO = 0, _VAO = 0;
	
	int _triangleCount = 0;

public:
	Texture getTexture() const { return _diffuseTexture; };
	GLsizei getNumIndices() const { return _numIndices; };

	virtual void Draw(Program& program) const = 0;
	virtual void applyTransformation(const glm::mat4& transform) = 0;
	int getTriangleCount() const { return _triangleCount; }
};