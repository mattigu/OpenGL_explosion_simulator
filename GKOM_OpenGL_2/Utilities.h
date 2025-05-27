#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "RegularMesh.h"
#include "InstancedMesh.h"
#include <vector>

GLuint LoadBox(GLenum* primitive, unsigned int* count);
RegularMesh LoadBoxMesh();
InstancedMesh LoadBoxMeshInstanced();