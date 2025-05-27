#pragma once

#include "Mesh.h"

class RegularMesh : public Mesh {
private:
	glm::mat4 _modelMatrix;
public:
	RegularMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture diffuseTexture, glm::mat4 modelMatrix = glm::mat4(1.0f))
		: Mesh(std::move(vertices), std::move(indices), std::move(diffuseTexture)), _modelMatrix(modelMatrix) {
	};

	void Draw(Program& program) const final override;

	void setModelMatrix(glm::mat4 newModel);
	// probably some applyTransformation function for the Model to affect things here
};