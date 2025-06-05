#pragma once

#include "Mesh.h"
#include "RegularMesh.h"

class RegularMesh;

class InstancedMesh : public Mesh {
private:
	GLenum _instanceBufferType = GL_DYNAMIC_DRAW;
	GLuint _instanceVBO;
	std::vector<glm::mat4> _instanceMatrices;

	void setupInstancing();
	void updateInstanceVBO() const;
	void remakeInstanceVBO() const;

public:
	InstancedMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture diffuseTexture,
		std::vector<glm::mat4> instanceMatrices, glm::mat4 modelMatrix = glm::mat4(1.0f))
		: Mesh(vertices, indices, diffuseTexture, modelMatrix), _instanceMatrices(std::move(instanceMatrices)) {
		setupInstancing();
	};

	virtual ~InstancedMesh() override;

	void Draw(Program& program) const final override;
	void applyTransformation(const glm::mat4& transform) final override;

	void setInstanceMatrices(const std::vector<glm::mat4>& instanceMatrices);

	int getTriangleCount() const override { return _numIndices / 3 * _instanceMatrices.size(); };
};
