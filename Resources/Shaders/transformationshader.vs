#version 330 core

layout (location = 0) in vec3 attrPosition;
layout (location = 1) in vec3 attrColor;

out VS_OUT {
    vec3 vColor;
} vs_out;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

out vec3 vWorldPos;

void main()
{
    vs_out.vColor = attrColor;

    gl_Position = uModelMatrix * vec4(attrPosition, 1.0);
}