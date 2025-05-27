#version 330 core

layout (location = 0) in vec3 attrPosition;
layout (location = 1) in vec3 attrNormals;
layout (location = 2) in vec4 attrColor;
layout (location = 3) in vec2 attrTextureCoords;
layout (location = 4) in mat4 attrInstanceMatrix;

out VS_OUT {
    vec4 Color;
    vec2 TextureCoords;
} vs_out;

uniform bool useInstancing;
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

void main()
{
    vs_out.Color = attrColor;
    mat4 modelMatrix = useInstancing ? attrInstanceMatrix : uModelMatrix;

    gl_Position = modelMatrix * vec4(attrPosition, 1.0);
}