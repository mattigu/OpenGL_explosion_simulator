#pragma once
#include "Model.h"
class InstancedModel : public Model
{
private:
	std::vector<glm::mat4> _instanceMatrices;
	std::vector<std::shared_ptr<InstancedMesh>> _meshes;

	void createMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Texture& diffuseTexture, const glm::mat4& transform) final override;
public:
	InstancedModel(const fs::path& relativePath, const std::vector<glm::mat4>& instanceMatrices) :_instanceMatrices(instanceMatrices) {
		loadModel( _directory / relativePath);
	}

	void Draw(Program& program) const final override;
	void applyTransformation(const glm::mat4& transform) final override;
	int getTriangleCount() const final override;
};

