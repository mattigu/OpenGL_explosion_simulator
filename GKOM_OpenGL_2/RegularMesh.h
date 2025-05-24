#pragma once

#include "Mesh.h"

class RegularMesh : public Mesh {
public:
	RegularMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture diffuseTexture)
		: Mesh(vertices, indices, diffuseTexture) {};

	void setupMesh() override;
	void Draw(Program& program) override;
};