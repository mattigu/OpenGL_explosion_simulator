#pragma once

#include "UniformBuffer.h"
#include "Explosion.h"

class ExplosionUBuffer : public UniformBuffer {
private:
	static constexpr GLuint BindingPoint = 1;
	static constexpr GLsizei BufferSize = 32; // Manually precalculated including offsets

	//glm::vec3 explosionOrigin - 0
	//float explosionTime       - 16
	//float explosionStrength   - 20
	//float explosionSpeed      - 24

	Explosion& _explosion;

public:
	ExplosionUBuffer(Explosion& explosion) : UniformBuffer(BindingPoint, BufferSize), _explosion(explosion) {}
	~ExplosionUBuffer() = default;

	void updateUniforms() const final override;
};

