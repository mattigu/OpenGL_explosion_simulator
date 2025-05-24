#pragma once

#include "Mesh.h"

// Could separate InstancedMesh into variations which require: vec3 displacement or a full model matrices
class InstancedMesh : public Mesh {
private:
	std::vector<glm::mat4> _modelMatrices;

public:
	InstancedMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture diffuseTexture, std::vector<glm::mat4> modelMatrices)
		: Mesh(vertices, indices, diffuseTexture), _modelMatrices(modelMatrices) {};

	void setupMesh() override;  
	void Draw(Program& program) override;
};