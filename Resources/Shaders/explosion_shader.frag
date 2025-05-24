#version 330 core
out vec4 FragColor;

uniform sampler2D diffuseTexture;
uniform bool useTexture;

in GS_OUT {
    vec3 Color;
    vec2 TextureCoords;
} fs_in;

void main()
{
// This solution sucks but it's good enough until we have actual textures and then I might just remove the Color attribute completely
    if(useTexture) {
        FragColor = texture(diffuseTexture, fs_in.TextureCoords);
    } else {
        FragColor = vec4(fs_in.Color, 1.0);
    }

} 