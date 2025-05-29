#pragma once
#include "Model.h"

class RegularModel : public Model
{
public:
	RegularModel(const fs::path& path) : Model(path) {};

	//void setModelMatrix(const glm::mat4& newModel);
	//void applyTransformation(const glm::mat4& transform) final override;
};

