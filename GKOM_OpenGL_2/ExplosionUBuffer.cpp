#include "ExplosionUBuffer.h"



void ExplosionUBuffer::updateUniforms() const
{
	struct ExplosionUBOData {
		glm::vec4 explosionOrigin;  // for allignment for std140
		float explosionTime;
		float explosionStrength;
		float explosionSpeed;
	};

	ExplosionUBOData uboData;
	uboData.explosionOrigin = glm::vec4(_explosion.explosionOrigin, 0.0f);
	uboData.explosionTime = _explosion.explosionTime;
	uboData.explosionStrength = _explosion.explosionStrength;
	uboData.explosionSpeed = 0.0f;

	glBindBuffer(GL_UNIFORM_BUFFER, _UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ExplosionUBOData), &uboData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
