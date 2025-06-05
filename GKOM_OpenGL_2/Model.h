#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "Mesh.h"
#include "RegularMesh.h"

#include "Program.h"

#include <stb_image.h>

#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>     

namespace fs = std::filesystem;

class Model
{
private:
	inline static const fs::path _modelsDirectory = "../Resources/Models/"; // Directory where all models are stored

	void processNode(aiNode* node, const aiScene* scene, aiMatrix4x4& parentTransform);
	void processMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4& transform);

	static GLuint TextureFromFile(const fs::path& path);
	Texture loadDiffuseTexture(aiMaterial* mat) const;

	static glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4* from);

protected:
	Model() = default;

	fs::path _directory; // This model's directory

	void loadModel(const fs::path& path);
	virtual void createMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Texture& diffuseTexture, const glm::mat4& transform) = 0;

public:
	virtual void Draw(Program& program) const = 0;
	virtual void applyTransformation(const glm::mat4& transform) = 0;
	virtual int getTriangleCount() const = 0;
};

