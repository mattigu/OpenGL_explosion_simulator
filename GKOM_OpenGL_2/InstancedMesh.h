#pragma once

#include "Mesh.h"

// Could separate InstancedMesh into variations which require: vec3 displacement or a full model matrices
class InstancedMesh : public Mesh {
private:
	std::vector<glm::mat4> _modelMatrices;

public:
	InstancedMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Texture& diffuseTexture, const std::vector<glm::mat4>& modelMatrices)
		: Mesh(vertices, indices, diffuseTexture), _modelMatrices(modelMatrices) {
		setupMesh();
	};

	void setupMesh() final override;  
	void Draw(Program& program) final override;
};