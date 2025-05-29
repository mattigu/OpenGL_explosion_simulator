#include "InstancedMesh.h"

InstancedMesh::~InstancedMesh()
{
    glDeleteBuffers(1, &_instanceVBO);
    _instanceVBO = 0;
}

void InstancedMesh::setupInstancing()
{
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, _modelMatrices.size() * sizeof(glm::mat4), &_modelMatrices[0], GL_STATIC_DRAW);

    glBindVertexArray(_VAO);
    // set attribute pointers for matrix (4 times vec4)
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);

    glBindVertexArray(0);
}

void InstancedMesh::updateInstanceVBO() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, _modelMatrices.size() * sizeof(glm::mat4), &_modelMatrices[0], GL_STATIC_DRAW);
}

InstancedMesh InstancedMesh::fromRegularMesh(RegularMesh& mesh, std::vector<glm::mat4> modelMatrices)
{
    auto[vao, vbo, ebo] = mesh.releaseBuffers();
    return InstancedMesh(vao, vbo, ebo, mesh.getTexture(), mesh.getNumIndices(), std::move(modelMatrices));
}

void InstancedMesh::Draw(Program& program) const
{
    if (_diffuseTexture.id != 0) { // 0 when texture is not loaded
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _diffuseTexture.id);
        glUniform1i(program.GetUniformID("diffuseTexture"), 0);
    }
    glUniform1i(program.GetUniformID("useInstancing"), 1);

    glBindVertexArray(_VAO);
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(_numIndices), GL_UNSIGNED_INT, 0, _modelMatrices.size());

    glUniform1i(program.GetUniformID("useInstancing"), 0);
    glBindVertexArray(0);
}

void InstancedMesh::applyTransformation(const glm::mat4& transform)
{
    for (auto& m : _modelMatrices) {
        m = transform * m;
    }
    updateInstanceVBO();
}

void InstancedMesh::setModelMatrices(const std::vector<glm::mat4>& modelMatrices)
{
    _modelMatrices = modelMatrices;
    updateInstanceVBO();
}


