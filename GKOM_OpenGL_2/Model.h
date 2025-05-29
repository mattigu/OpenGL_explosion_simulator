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
protected:
	std::vector<std::shared_ptr<Mesh>> _meshes;
	fs::path _directory; // This model's directory
	
	Model(const fs::path& path);

	void loadModel(const fs::path& path);
	void processNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);

	Texture loadDiffuseTexture(aiMaterial* mat) const;
	static GLuint TextureFromFile(const fs::path& path);
public:
	void Draw(Program& program) const;

	//virtual void applyTransformation(const glm::mat4& transform) = 0;
};

