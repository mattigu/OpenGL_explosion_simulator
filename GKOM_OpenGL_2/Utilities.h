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
std::vector<glm::mat4> getSampleInstanceMatrices();
std::vector<glm::mat4> getSampleInstanceMatricesCube(int size);
std::vector<Vertex> getBoxVertices();
std::vector<unsigned int> getBoxIndices();

RegularMesh LoadSphereMesh(glm::vec4 color);
std::vector<Vertex> getSphereVertices(glm::vec4 color);
std::vector<unsigned int> getSphereIndices();