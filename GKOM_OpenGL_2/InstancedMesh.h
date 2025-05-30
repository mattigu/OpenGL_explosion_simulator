#pragma once

#include "Mesh.h"
#include "RegularMesh.h"

class RegularMesh;

class InstancedMesh : public Mesh {
private:
	GLuint _instanceVBO;
	std::vector<glm::mat4> _modelMatrices;

	void setupInstancing();
	void updateInstanceVBO() const;

public:
	InstancedMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Texture diffuseTexture, std::vector<glm::mat4> modelMatrices = { glm::mat4(1.0f) })
		: Mesh(vertices, indices, diffuseTexture), _modelMatrices(std::move(modelMatrices)) {
		setupInstancing();
	};

	// Usually not called explictly, used in fromRegularMesh to convert meshes with copying buffers. 
	InstancedMesh(GLuint vao, GLuint vbo, GLuint ebo, Texture texture, GLsizei indexCount, std::vector<glm::mat4> modelMatrices)
		: Mesh(vao, vbo, ebo, texture, indexCount), _modelMatrices(std::move(modelMatrices)) {
		setupInstancing();
	}

	virtual ~InstancedMesh() override;

	static InstancedMesh fromRegularMesh(RegularMesh& mesh, std::vector<glm::mat4> modelMatrices);

	void Draw(Program& program) const final override;
	void applyTransformation(const glm::mat4& transform) final override;

	void setModelMatrices(const std::vector<glm::mat4>& modelMatrices);
};



// Could add something like this later to modify singular model matrix

//void InstancedMesh::updateSingleInstance(int index) const
//{
//	glBindBuffer(GL_ARRAY_BUFFER, _instanceVBO);
//	glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(glm::mat4), sizeof(glm::mat4), &_modelMatrices[index]);
//}
