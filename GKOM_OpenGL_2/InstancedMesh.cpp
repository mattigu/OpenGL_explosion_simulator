#include "InstancedMesh.h"

void InstancedMesh::setupInstancing()
{
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

void InstancedMesh::setupMesh()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
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

    setupInstancing();
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
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, 0, _modelMatrices.size());

    glUniform1i(program.GetUniformID("useInstancing"), 0);
    glBindVertexArray(0);
}
