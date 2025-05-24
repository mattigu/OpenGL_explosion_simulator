#pragma once

#include "Mesh.h"

// Could separate InstancedMesh into variations which require: vec3 displacement or a full model matrices
class InstancedMesh : public Mesh {
private:
	std::vector<glm::mat4> _modelMatrices;

public:
	InstancedMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, std::vector<glm::mat4> modelMatrices)
		: Mesh(vertices, indices), _modelMatrices(modelMatrices) {};

	void setupMesh() override;  
	void Draw() override;
};