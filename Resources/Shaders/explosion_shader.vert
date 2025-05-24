#version 330 core

layout (location = 0) in vec3 attrPosition;
layout (location = 1) in vec3 attrColor;

out VS_OUT {
    vec3 Color;
} vs_out;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

void main()
{
    vs_out.Color = attrColor;

    gl_Position = uModelMatrix * vec4(attrPosition, 1.0);
}