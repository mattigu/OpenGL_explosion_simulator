#pragma once

#include "UniformBuffer.h"

class MatricesUBuffer : public UniformBuffer {
private:
	static constexpr GLuint BindingPoint = 0;
	static constexpr GLsizei BufferSize = 128; // 2 * mat4

	const glm::mat4& _projection;
	const glm::mat4& _view;

public:
	MatricesUBuffer(const glm::mat4& view, const glm::mat4& projection) : UniformBuffer(BindingPoint, BufferSize), _projection(projection), _view(view) {}
	~MatricesUBuffer() = default;

	void updateUniforms() const final override;
};