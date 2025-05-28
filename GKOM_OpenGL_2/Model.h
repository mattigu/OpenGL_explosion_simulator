#pragma once

#include <string>
#include <vector>

#include "Mesh.h"
#include "Program.h"

#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>     

class Model
{
protected:
	std::vector<Texture> textures_loaded;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::string directory;
	
	Model(const std::string& path);

	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	static unsigned int TextureFromFile(const char* path, const std::string& directory);
public:
	virtual void Draw(Program& program) const;
};

