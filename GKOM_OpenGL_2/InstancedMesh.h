#pragma once

#include "Mesh.h"
#include "RegularMesh.h"

class RegularMesh;

class InstancedMesh : public Mesh {
private:
	GLenum _instanceBufferType = GL_DYNAMIC_DRAW;
	GLuint _instanceVBO;
	std::vector<glm::mat4> _modelMatrices;

	void setupInstancing();
	void updateInstanceVBO() const;
	void remakeInstanceVBO() const;

public:
	InstancedMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture diffuseTexture, std::vector<glm::mat4> modelMatrices = { glm::mat4(1.0f) })
		: Mesh(vertices, indices, diffuseTexture), _modelMatrices(std::move(modelMatrices)) {
		setupInstancing();
	};

	virtual ~InstancedMesh() override;

	void Draw(Program& program) const final override;
	void applyTransformation(const glm::mat4& transform) final override;

	void setModelMatrices(const std::vector<glm::mat4>& modelMatrices);

	int getTriangleCount() const override { return _numIndices / 3 * _modelMatrices.size(); };
};
