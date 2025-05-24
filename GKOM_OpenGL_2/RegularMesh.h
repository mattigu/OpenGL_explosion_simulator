#pragma once

#include "Mesh.h"

class RegularMesh : public Mesh {
public:
	RegularMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		: Mesh(vertices, indices) {};

	void setupMesh() override;
	void Draw() override;
};