#include "UniformBuffer.h"


UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &_buffer);
	_buffer = 0;
}


void UniformBuffer::setupBuffer()
{

}


