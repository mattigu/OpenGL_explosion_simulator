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

    std::vector<glm::vec4> colors;
    // Front face
    colors.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    // Back face             
    colors.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    // Top face           
    colors.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    // Bottom face           
    colors.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));
    // Left face             
    colors.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 0.0f));
    // Right face            
    colors.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));
    colors.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));
   
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

    //struct Vertex
    //{
    //    glm::vec3 position;
    //    glm::vec3 color;
    //    glm::vec2 textCoords;
    //};

    std::vector<Vertex> BufferData;

    for (size_t i = 0; i < positions.size(); i++)
    {
        BufferData.push_back({ positions[i], glm::vec3(0.0, 0.0, 0.0), colors[i], glm::vec2(0.0, 0.0) });
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

RegularMesh LoadBoxMesh()
{
    // Temporary ugly function to test if meshes work
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec4 green = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    glm::vec4 blue = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

    glm::vec2 uv00 = glm::vec2(0.0f, 0.0f);
    glm::vec2 uv01 = glm::vec2(0.0f, 1.0f);
    glm::vec2 uv10 = glm::vec2(1.0f, 0.0f);
    glm::vec2 uv11 = glm::vec2(1.0f, 1.0f);

    // FRONT FACE (+Z)
    glm::vec3 normalFront = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(Vertex(glm::vec3(-1, -1, 1), normalFront, red, uv00)); // 0
    vertices.push_back(Vertex(glm::vec3(1, -1, 1), normalFront, red, uv10)); // 1
    vertices.push_back(Vertex(glm::vec3(1, 1, 1), normalFront, red, uv11)); // 2
    vertices.push_back(Vertex(glm::vec3(-1, 1, 1), normalFront, red, uv01)); // 3

    // BACK FACE (-Z)
    glm::vec3 normalBack = glm::vec3(0.0f, 0.0f, -1.0f);
    vertices.push_back(Vertex(glm::vec3(1, -1, -1), normalBack, green, uv00)); // 4
    vertices.push_back(Vertex(glm::vec3(-1, -1, -1), normalBack, green, uv10)); // 5
    vertices.push_back(Vertex(glm::vec3(-1, 1, -1), normalBack, green, uv11)); // 6
    vertices.push_back(Vertex(glm::vec3(1, 1, -1), normalBack, green, uv01)); // 7

    // RIGHT FACE (+X)
    glm::vec3 normalRight = glm::vec3(1.0f, 0.0f, 0.0f);
    vertices.push_back(Vertex(glm::vec3(1, -1, 1), normalRight, blue, uv00));  // 8
    vertices.push_back(Vertex(glm::vec3(1, -1, -1), normalRight, blue, uv10)); // 9
    vertices.push_back(Vertex(glm::vec3(1, 1, -1), normalRight, blue, uv11)); // 10
    vertices.push_back(Vertex(glm::vec3(1, 1, 1), normalRight, blue, uv01)); // 11

    // LEFT FACE (-X)
    glm::vec3 normalLeft = glm::vec3(-1.0f, 0.0f, 0.0f);
    vertices.push_back(Vertex(glm::vec3(-1, -1, -1), normalLeft, red, uv00));  // 12
    vertices.push_back(Vertex(glm::vec3(-1, -1, 1), normalLeft, red, uv10));  // 13
    vertices.push_back(Vertex(glm::vec3(-1, 1, 1), normalLeft, red, uv11));  // 14
    vertices.push_back(Vertex(glm::vec3(-1, 1, -1), normalLeft, red, uv01));  // 15

    // TOP FACE (+Y)
    glm::vec3 normalTop = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices.push_back(Vertex(glm::vec3(-1, 1, 1), normalTop, green, uv00));  // 16
    vertices.push_back(Vertex(glm::vec3(1, 1, 1), normalTop, green, uv10));  // 17
    vertices.push_back(Vertex(glm::vec3(1, 1, -1), normalTop, green, uv11));  // 18
    vertices.push_back(Vertex(glm::vec3(-1, 1, -1), normalTop, green, uv01));  // 19

    // BOTTOM FACE (-Y)
    glm::vec3 normalBottom = glm::vec3(0.0f, -1.0f, 0.0f);
    vertices.push_back(Vertex(glm::vec3(-1, -1, -1), normalBottom, blue, uv00)); // 20
    vertices.push_back(Vertex(glm::vec3(1, -1, -1), normalBottom, blue, uv10)); // 21
    vertices.push_back(Vertex(glm::vec3(1, -1, 1), normalBottom, blue, uv11)); // 22
    vertices.push_back(Vertex(glm::vec3(-1, -1, 1), normalBottom, blue, uv01)); // 23

    // Add indices for each face (two triangles per face)
    for (int i = 0; i < 6; ++i) {
        unsigned int base = i * 4;
        indices.insert(indices.end(), {
            base + 0, base + 1, base + 2,
            base + 0, base + 2, base + 3
            });
    }
    Texture text;
    RegularMesh mesh(vertices, indices, text);
    return mesh;
}

InstancedMesh LoadBoxMeshInstanced()
{
    // Temporary ugly function to test if meshes work
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec4 green = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    glm::vec4 blue = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

    glm::vec2 uv00 = glm::vec2(0.0f, 0.0f);
    glm::vec2 uv01 = glm::vec2(0.0f, 1.0f);
    glm::vec2 uv10 = glm::vec2(1.0f, 0.0f);
    glm::vec2 uv11 = glm::vec2(1.0f, 1.0f);

    // FRONT FACE (+Z)
    glm::vec3 normalFront = glm::vec3(0.0f, 0.0f, 1.0f);
    vertices.push_back(Vertex(glm::vec3(-1, -1, 1), normalFront, red, uv00)); // 0
    vertices.push_back(Vertex(glm::vec3(1, -1, 1), normalFront, red, uv10)); // 1
    vertices.push_back(Vertex(glm::vec3(1, 1, 1), normalFront, red, uv11)); // 2
    vertices.push_back(Vertex(glm::vec3(-1, 1, 1), normalFront, red, uv01)); // 3

    // BACK FACE (-Z)
    glm::vec3 normalBack = glm::vec3(0.0f, 0.0f, -1.0f);
    vertices.push_back(Vertex(glm::vec3(1, -1, -1), normalBack, green, uv00)); // 4
    vertices.push_back(Vertex(glm::vec3(-1, -1, -1), normalBack, green, uv10)); // 5
    vertices.push_back(Vertex(glm::vec3(-1, 1, -1), normalBack, green, uv11)); // 6
    vertices.push_back(Vertex(glm::vec3(1, 1, -1), normalBack, green, uv01)); // 7

    // RIGHT FACE (+X)
    glm::vec3 normalRight = glm::vec3(1.0f, 0.0f, 0.0f);
    vertices.push_back(Vertex(glm::vec3(1, -1, 1), normalRight, blue, uv00));  // 8
    vertices.push_back(Vertex(glm::vec3(1, -1, -1), normalRight, blue, uv10)); // 9
    vertices.push_back(Vertex(glm::vec3(1, 1, -1), normalRight, blue, uv11)); // 10
    vertices.push_back(Vertex(glm::vec3(1, 1, 1), normalRight, blue, uv01)); // 11

    // LEFT FACE (-X)
    glm::vec3 normalLeft = glm::vec3(-1.0f, 0.0f, 0.0f);
    vertices.push_back(Vertex(glm::vec3(-1, -1, -1), normalLeft, red, uv00));  // 12
    vertices.push_back(Vertex(glm::vec3(-1, -1, 1), normalLeft, red, uv10));  // 13
    vertices.push_back(Vertex(glm::vec3(-1, 1, 1), normalLeft, red, uv11));  // 14
    vertices.push_back(Vertex(glm::vec3(-1, 1, -1), normalLeft, red, uv01));  // 15

    // TOP FACE (+Y)
    glm::vec3 normalTop = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices.push_back(Vertex(glm::vec3(-1, 1, 1), normalTop, green, uv00));  // 16
    vertices.push_back(Vertex(glm::vec3(1, 1, 1), normalTop, green, uv10));  // 17
    vertices.push_back(Vertex(glm::vec3(1, 1, -1), normalTop, green, uv11));  // 18
    vertices.push_back(Vertex(glm::vec3(-1, 1, -1), normalTop, green, uv01));  // 19

    // BOTTOM FACE (-Y)
    glm::vec3 normalBottom = glm::vec3(0.0f, -1.0f, 0.0f);
    vertices.push_back(Vertex(glm::vec3(-1, -1, -1), normalBottom, blue, uv00)); // 20
    vertices.push_back(Vertex(glm::vec3(1, -1, -1), normalBottom, blue, uv10)); // 21
    vertices.push_back(Vertex(glm::vec3(1, -1, 1), normalBottom, blue, uv11)); // 22
    vertices.push_back(Vertex(glm::vec3(-1, -1, 1), normalBottom, blue, uv01)); // 23

    // Add indices for each face (two triangles per face)
    for (int i = 0; i < 6; ++i) {
        unsigned int base = i * 4;
        indices.insert(indices.end(), {
            base + 0, base + 1, base + 2,
            base + 0, base + 2, base + 3
            });
    }

    Texture text;
    InstancedMesh mesh(vertices, indices, text, getSampleInstanceMatrices());
    return mesh;
}

std::vector<glm::mat4> getSampleInstanceMatrices()
{
    std::vector<glm::mat4> instanceMatrices;
    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            instanceMatrices.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i * 3.0f, j * 3.0f, 0.0f)));
        }
    }
    return instanceMatrices;
}

std::vector<glm::mat4> getSampleInstanceMatricesCube(int size)
{
    std::vector<glm::mat4> instanceMatrices;
    for (int i = -size; i <= size; i++)
    {
        for (int j = -size; j <= size; j++)
        {
            for (int k = -size; k <= size; k++)
            {
                instanceMatrices.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i * 3.0f, j * 3.0f, k * 3.0f)));
            }
        }
    }
    return instanceMatrices;
}
