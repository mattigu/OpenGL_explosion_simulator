#pragma once

#include "Mesh.h"

class RegularMesh : public Mesh {
public:
	RegularMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Texture& diffuseTexture)
		: Mesh(vertices, indices, diffuseTexture) {
		setupMesh();
	};

	void setupMesh() final override;
	void Draw(Program& program) final override;
};