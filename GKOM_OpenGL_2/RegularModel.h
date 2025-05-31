#pragma once
#include "Model.h"

class RegularModel : public Model
{
private:
	std::vector<std::shared_ptr<RegularMesh>> _meshes;

	void createMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Texture& diffuseTexture) final override;
public:
	RegularModel(const fs::path& relativePath, GLenum bufferType = GL_STATIC_DRAW) : Model(bufferType) {
		loadModel(_directory / relativePath); 
	};

	void Draw(Program& program) const final override;
	//void setModelMatrix(const glm::mat4& newModel);
	void applyTransformation(const glm::mat4& transform) final override;
};

