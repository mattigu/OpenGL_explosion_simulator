#include "UniformBuffer.h"


UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &_UBO);
	_UBO = 0;
}


void UniformBuffer::setupBuffer()
{
	glGenBuffers(1, &_UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, _UBO);
	glBufferData(GL_UNIFORM_BUFFER, _bufferSize, NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, _bindingPoint, _UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


