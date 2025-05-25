#include "Utilities.h"

GLuint LoadBox(GLenum* primitive, unsigned int* count)
{
    GLuint VBO;
    GLuint VAO;

    std::vector<glm::vec3> positions;
    // Front face
    positions.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
    // Back face
    positions.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
    // Top face
    positions.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
    // Bottom face
    positions.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    // Left face
    positions.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
    // Right face
    positions.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));

    std::vector<glm::vec3> colors;
    // Front face
    colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    // Back face
    colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    // Top face
    colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    // Bottom face
    colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
    // Left face
    colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
    colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
    colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
    colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
    colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
    colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
    // Right face
    colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
    colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
    colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
    colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
    colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
    colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));

    //std::vector<glm::vec3> normals;
    //// Front face
    //normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    //normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    //normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    //normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    //normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    //normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    //// Back face
    //normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    //normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    //normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    //normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    //normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    //normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    //// Top face
    //normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    //normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    //normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    //normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    //normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    //normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    //// Bottom face
    //normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    //normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    //normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    //normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    //normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    //normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    //// Left face
    //normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    //normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    //normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    //normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    //normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    //normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    //// Right face
    //normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));
    //normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));
    //normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));
    //normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));
    //normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));
    //normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 textCoords;
    };

    std::vector<Vertex> BufferData;

    for (size_t i = 0; i < positions.size(); i++)
    {
        BufferData.push_back({ positions[i], colors[i], glm::vec2(0.0, 0.0)});
    }

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * BufferData.size(), BufferData.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    *count = BufferData.size();
    *primitive = GL_TRIANGLES;

    return VAO;
}