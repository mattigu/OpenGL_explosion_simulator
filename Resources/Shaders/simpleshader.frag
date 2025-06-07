#version 420 core
out vec4 FragColor;

in VS_OUT {
    vec4 Color;
    vec2 TextureCoords;
} fs_in;

uniform sampler2D diffuseTexture;
uniform bool useTexture;

void main()
{
    if(useTexture) {
        FragColor = texture(diffuseTexture, fs_in.TextureCoords);
    } else {
        FragColor = vec4(fs_in.Color);
    }
} 