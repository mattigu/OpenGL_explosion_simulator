#include "RegularModel.h"

void RegularModel::createMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Texture& diffuseTexture, const glm::mat4& transform)
{
	auto mesh = std::make_shared<RegularMesh>(vertices, indices, diffuseTexture, transform);
	_meshes.push_back(mesh);
}

void RegularModel::Draw(Program& program) const
{
	for (const auto& meshPtr : _meshes) {
		meshPtr->Draw(program);
	}
}

void RegularModel::applyTransformation(const glm::mat4& transform)
{
	for (const auto& meshPtr : _meshes) {
		meshPtr->applyTransformation(transform);
	}
}

int RegularModel::getTriangleCount() const
{
	int count = 0;
	for (const auto& meshPtr : _meshes) {
		count += meshPtr->getTriangleCount();
	}
	return count;
}
