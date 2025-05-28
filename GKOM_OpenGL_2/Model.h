#pragma once

#include <string>
#include <vector>

#include "Mesh.h"
#include "Program.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

class Model
{
protected:
	std::vector<Texture> textures_loaded;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::string directory;
	
	void loadModel(std::string const& path);
	// assimp params below so keeping them empty 
	void processNode(); 
	Mesh processMesh();
	std::vector<Texture> loadMaterialTextures();
	unsigned int TextureFromFile();
public:
	virtual void Draw(Program& program);

};

