#include "RegularMesh.h"

std::tuple<GLuint, GLuint, GLuint> RegularMesh::releaseBuffers()
{
    auto tmp = std::make_tuple(_VAO, _VBO, _EBO);
    _VAO = _VBO = _EBO = 0;
    return tmp;
}

void RegularMesh::Draw(Program& program) const
{
    if (_diffuseTexture.id != 0) { // 0 when texture is not loaded
        glUniform1i(program.GetUniformID("useTexture"), 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _diffuseTexture.id);
        glUniform1i(program.GetUniformID("diffuseTexture"), 0);
    }

    glUniformMatrix4fv(program.GetUniformID("uModelMatrix"), 1, GL_FALSE, glm::value_ptr(_modelMatrix));
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, (_numIndices), GL_UNSIGNED_INT, 0);

    glUniform1i(program.GetUniformID("useTexture"), 0);

    glBindVertexArray(0);
}

void RegularMesh::applyTransformation(const glm::mat4& transform)
{
    _modelMatrix = _modelMatrix * transform;
}

void RegularMesh::setModelMatrix(const glm::mat4& newModel)
{
    _modelMatrix = newModel;
}

