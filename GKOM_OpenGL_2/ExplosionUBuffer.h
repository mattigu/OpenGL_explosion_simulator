#pragma once

#include "UniformBuffer.h"

struct Explosion {}; // temp explosion struct

class ExplosionUBuffer : public UniformBuffer {
private:
	static constexpr GLuint BindingPoint = 1;
	static constexpr GLsizei BufferSize = 10; // Manually precalculated including offsets

	const Explosion& _explosion;

public:
	ExplosionUBuffer(const Explosion& explosion) : UniformBuffer(BindingPoint, BufferSize), _explosion(explosion) {}
	~ExplosionUBuffer() = default;

	void updateUniforms() final override;
};

