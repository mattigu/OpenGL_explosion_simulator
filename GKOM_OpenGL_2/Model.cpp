#include "Model.h"

void Model::loadModel(const fs::path& path)
{
    fs::path fullPath = _modelsDirectory / path;
    Assimp::Importer importer;

    unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs;

    const aiScene* scene = importer.ReadFile(fullPath.string(), flags);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    _directory = fullPath.parent_path();

    aiMatrix4x4 identity;
    processNode(scene->mRootNode, scene, identity);
}

void Model::processNode(aiNode* node, const aiScene* scene, aiMatrix4x4& parentTransform)
{
    aiMatrix4x4 currentTransform = parentTransform * node->mTransformation;
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene, currentTransform);
    }
    // process children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, currentTransform);
    }
}

void Model::processMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4& transform)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    vertices.reserve(mesh->mNumVertices);
    indices.reserve(mesh->mNumFaces * 3);

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; 
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }
    // get indices for each face
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    Texture diffuseTexture;
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        diffuseTexture = loadDiffuseTexture(material);
    }

    createMesh(vertices, indices, diffuseTexture, aiMatrix4x4ToGlm(&transform));
}

Texture Model::loadDiffuseTexture(aiMaterial* mat) const
{
    aiString str;
    Texture texture;

    if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        fs::path fullPath = _directory / fs::path(str.C_Str()).filename();

        texture.id = TextureFromFile(fullPath);
    }
    return texture;
}

GLuint Model::TextureFromFile(const fs::path& path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
        textureID = 0;
    }

    return textureID;
}

glm::mat4 Model::aiMatrix4x4ToGlm(const aiMatrix4x4* from)
{
    glm::mat4 to;

    to[0][0] = (GLfloat)from->a1; to[0][1] = (GLfloat)from->b1;  to[0][2] = (GLfloat)from->c1; to[0][3] = (GLfloat)from->d1;
    to[1][0] = (GLfloat)from->a2; to[1][1] = (GLfloat)from->b2;  to[1][2] = (GLfloat)from->c2; to[1][3] = (GLfloat)from->d2;
    to[2][0] = (GLfloat)from->a3; to[2][1] = (GLfloat)from->b3;  to[2][2] = (GLfloat)from->c3; to[2][3] = (GLfloat)from->d3;
    to[3][0] = (GLfloat)from->a4; to[3][1] = (GLfloat)from->b4;  to[3][2] = (GLfloat)from->c4; to[3][3] = (GLfloat)from->d4;

    return to;
}

