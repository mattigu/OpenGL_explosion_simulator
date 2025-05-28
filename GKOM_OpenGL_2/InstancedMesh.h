#pragma once

#include "Mesh.h"

// Could separate InstancedMesh into variations which require: vec3 displacement or a full model matrices
class InstancedMesh : public Mesh {
private:
	GLuint _instanceVBO;
	std::vector<glm::mat4> _modelMatrices;
	void setupInstancing();
	void updateInstanceVBO() const;

public: // change to std::move
	InstancedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture diffuseTexture, std::vector<glm::mat4> modelMatrices)
		: Mesh(std::move(vertices), std::move(indices), std::move(diffuseTexture)),
			_modelMatrices(std::move(modelMatrices)) {
		setupInstancing();
	};

	void Draw(Program& program) const final override;
	virtual void applyTransformation(const glm::mat4& transform) final override;
	void setModelMatrices(const std::vector<glm::mat4>& modelMatrices);
};

// Could add something like this later to modify singular model matrix

//void InstancedMesh::updateSingleInstance(int index) const
//{
//	glBindBuffer(GL_ARRAY_BUFFER, _instanceVBO);
//	glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(glm::mat4), sizeof(glm::mat4), &_modelMatrices[index]);
//}
