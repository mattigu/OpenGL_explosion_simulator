#include <unordered_map>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

class UniformBuffer {
private:
	void setupBuffer();

protected:
	GLuint _bindingPoint;
	GLuint _UBO;
	GLsizei _bufferSize;
	
	UniformBuffer(GLuint bindingBlock, GLsizei bufferSize) : _bindingPoint(bindingBlock), _bufferSize(bufferSize) {
		setupBuffer();
	};
	~UniformBuffer();

public:
	virtual void updateUniforms() const = 0;
};