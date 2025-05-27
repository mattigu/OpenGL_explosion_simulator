#include "RegularMesh.h"

void RegularMesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex colors
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    // vertex texture coords
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void RegularMesh::Draw(Program& program)
{
    if (_diffuseTexture.id != 0) { // 0 when texture is not loaded
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _diffuseTexture.id);
        glUniform1i(program.GetUniformID("diffuseTexture"), 0);
    }

    glUniformMatrix4fv(program.GetUniformID("uModelMatrix"), 1, GL_FALSE, glm::value_ptr(_modelMatrix));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (_indices.size()), GL_UNSIGNED_INT, 0);


    glBindVertexArray(0);
}

void RegularMesh::setModelMatrix(glm::mat4 newModel)
{
    _modelMatrix = newModel;
}
