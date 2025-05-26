#version 330 core

layout (location = 0) in vec3 attrPosition;
layout (location = 1) in vec3 attrNormals;
layout (location = 2) in vec4 attrColor;
layout (location = 3) in vec2 attrTextureCoords;

out VS_OUT {
    vec4 Color;
    vec2 TextureCoords;
} vs_out;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

void main()
{
    vs_out.Color = attrColor;

    gl_Position = uModelMatrix * vec4(attrPosition, 1.0);
}