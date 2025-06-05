#pragma once

#include "Mesh.h"
#include "InstancedMesh.h"

class RegularMesh : public Mesh {
public:
	RegularMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture diffuseTexture, glm::mat4 modelMatrix = glm::mat4(1.0f))
		: Mesh(vertices, indices, diffuseTexture, modelMatrix) {
	};
	~RegularMesh() override = default;

	void Draw(Program& program) const final override;

	void setModelMatrix(const glm::mat4& newModel);
	int getTriangleCount() const override { return _numIndices / 3; };
};

