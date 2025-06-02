#include "InstancedModel.h"

void InstancedModel::createMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Texture& diffuseTexture)
{
	_meshes.push_back(std::make_shared<InstancedMesh>(vertices, indices, diffuseTexture, _modelMatrices));
}

void InstancedModel::Draw(Program& program) const
{
	for (const auto& meshPtr : _meshes) {
		meshPtr->Draw(program);
	}
}

void InstancedModel::applyTransformation(const glm::mat4& transform)
{
	for (const auto& meshPtr : _meshes) {
		meshPtr->applyTransformation(transform);
	}
}

int InstancedModel::getTriangleCount() const
{
	int count = 0;
	for (const auto& meshPtr : _meshes) {
		count += meshPtr->getTriangleCount();
	}
	return count;
}
