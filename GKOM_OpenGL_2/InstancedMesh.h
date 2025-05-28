#pragma once

#include "Mesh.h"

// Could separate InstancedMesh into variations which require: vec3 displacement or a full model matrices
class InstancedMesh : public Mesh {
private:
	GLuint _instanceVBO;
	std::vector<glm::mat4> _modelMatrices;
	void setupInstancing();

public: // change to std::move
	InstancedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture diffuseTexture, std::vector<glm::mat4> modelMatrices)
		: Mesh(std::move(vertices), std::move(indices), std::move(diffuseTexture)),
			_modelMatrices(std::move(modelMatrices)) {
		setupInstancing();
	};

	void Draw(Program& program) const final override;
	// Add functions to modify and update the buffer - note below 
	//glBindBuffer(GL_ARRAY_BUFFER, _instancevbo);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(newData), newData);
};