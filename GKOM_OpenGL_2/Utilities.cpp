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
    Texture text;
    RegularMesh mesh(getBoxVertices(), getBoxIndices(), text);
    return mesh;
}

RegularMesh LoadSphereMesh(glm::vec4 color)
{
    Texture text;
    RegularMesh mesh(getSphereVertices(color), getSphereIndices(), text);
    return mesh;
}

InstancedMesh LoadBoxMeshInstanced()
{

    Texture text;
    InstancedMesh mesh(getBoxVertices(), getBoxIndices(), text, getSampleInstanceMatrices());
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

std::vector<Vertex> getBoxVertices()
{
    std::vector<Vertex> vertices = {
        // Front face (red)
        {{ 1.0f,  1.0f,  1.0f}, {}, {1, 0, 0, 1}, {}},
        {{-1.0f,  1.0f,  1.0f}, {}, {1, 0, 0, 1}, {}},
        {{-1.0f, -1.0f,  1.0f}, {}, {1, 0, 0, 1}, {}},
        {{ 1.0f, -1.0f,  1.0f}, {}, {1, 0, 0, 1}, {}},

        // Back face (green)
        {{ 1.0f, -1.0f, -1.0f}, {}, {0, 1, 0, 1}, {}},
        {{-1.0f, -1.0f, -1.0f}, {}, {0, 1, 0, 1}, {}},
        {{-1.0f,  1.0f, -1.0f}, {}, {0, 1, 0, 1}, {}},
        {{ 1.0f,  1.0f, -1.0f}, {}, {0, 1, 0, 1}, {}},

        // Top face (blue)
        {{ 1.0f,  1.0f, -1.0f}, {}, {0, 0, 1, 1}, {}},
        {{-1.0f,  1.0f, -1.0f}, {}, {0, 0, 1, 1}, {}},
        {{-1.0f,  1.0f,  1.0f}, {}, {0, 0, 1, 1}, {}},
        {{ 1.0f,  1.0f,  1.0f}, {}, {0, 0, 1, 1}, {}},

        // Bottom face (yellow)
        {{ 1.0f, -1.0f,  1.0f}, {}, {1, 1, 0, 1}, {}},
        {{-1.0f, -1.0f,  1.0f}, {}, {1, 1, 0, 1}, {}},
        {{-1.0f, -1.0f, -1.0f}, {}, {1, 1, 0, 1}, {}},
        {{ 1.0f, -1.0f, -1.0f}, {}, {1, 1, 0, 1}, {}},

        // Left face (magenta)
        {{-1.0f,  1.0f,  1.0f}, {}, {1, 0, 1, 1}, {}},
        {{-1.0f,  1.0f, -1.0f}, {}, {1, 0, 1, 1}, {}},
        {{-1.0f, -1.0f, -1.0f}, {}, {1, 0, 1, 1}, {}},
        {{-1.0f, -1.0f,  1.0f}, {}, {1, 0, 1, 1}, {}},

        // Right face (cyan)
        {{ 1.0f,  1.0f, -1.0f}, {}, {0, 1, 1, 1}, {}},
        {{ 1.0f,  1.0f,  1.0f}, {}, {0, 1, 1, 1}, {}},
        {{ 1.0f, -1.0f,  1.0f}, {}, {0, 1, 1, 1}, {}},
        {{ 1.0f, -1.0f, -1.0f}, {}, {0, 1, 1, 1}, {}},
    };
    return vertices;
}

std::vector<unsigned int> getBoxIndices()
{
    std::vector<GLuint> indices = {
        // Front
        0, 1, 2,
        0, 2, 3,

        // Back
        4, 5, 6,
        4, 6, 7,

        // Top
        8, 9,10,
        8,10,11,

        // Bottom
       12,13,14,
       12,14,15,

       // Left
      16,17,18,
      16,18,19,

      // Right
     20,21,22,
     20,22,23,
    };

    return indices;
}

std::vector<Vertex> getSphereVertices(glm::vec4 color)
{
    std::vector<Vertex> vertices;

    unsigned int res = 100;
    float circleStep = glm::two_pi<float>() / (float)res;
    float heightStep = glm::pi<float>() / (float)res;

    int row = 0;

    float phi = -glm::half_pi<float>();
    float y = glm::sin(phi);
    float radius;

    for (; phi < glm::half_pi<float>() + heightStep; phi += heightStep, row++)
    {
        y = glm::sin(phi);
        radius = glm::cos(phi);
        int cell = 0;

        for (float th = 0; th < glm::two_pi<float>(); cell++) 
        {
            th += circleStep;
            vertices.push_back({ {radius * glm::cos(th), y, radius * glm::sin(th)}, {}, color , {} });
        }
    }
    return vertices;
}

std::vector<unsigned int> getSphereIndices() 
{
    std::vector<GLuint> indices;
    int noVertices = 0;

    unsigned int res = 100;
    float circleStep = glm::two_pi<float>() / (float)res;
    float heightStep = glm::pi<float>() / (float)res;

    int row = 0;

    float phi = -glm::half_pi<float>();
    float y = glm::sin(phi);
    float radius;

    for (; phi < glm::half_pi<float>() + heightStep; phi += heightStep, row++) {
        int cell = 0;
        for (float th = 0; th < glm::two_pi<float>(); th += circleStep, cell++) {
            if (row)
            {
                int nextCell = (cell + 1) % res;
                indices.push_back(noVertices - res); // bottom left
                indices.push_back((row - 1) * res + nextCell); // bottom right
                indices.push_back(row * res + nextCell); // top right

                indices.push_back(noVertices - res); // bottom left
                indices.push_back(noVertices); // top left (this vertex)
                indices.push_back(row * res + nextCell); // top right
            }
            noVertices++;
        }
    }
    return indices;
}
