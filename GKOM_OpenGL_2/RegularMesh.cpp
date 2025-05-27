#include "RegularMesh.h"

void RegularMesh::Draw(Program& program) const
{
    if (_diffuseTexture.id != 0) { // 0 when texture is not loaded
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _diffuseTexture.id);
        glUniform1i(program.GetUniformID("diffuseTexture"), 0);
    }

    glUniformMatrix4fv(program.GetUniformID("uModelMatrix"), 1, GL_FALSE, glm::value_ptr(_modelMatrix));
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, (_indices.size()), GL_UNSIGNED_INT, 0);


    glBindVertexArray(0);
}

void RegularMesh::setModelMatrix(glm::mat4 newModel)
{
    _modelMatrix = newModel;
}
