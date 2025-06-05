#version 330 core
out vec4 FragColor;

uniform sampler2D diffuseTexture;
uniform bool useTexture;

in GS_OUT {
    vec4 Color;
    vec2 TextureCoords;
    float timeSinceHit;
} fs_in;

const float timeToLive = 5.0f;
const float fadeDelay = 3.0f;

void main()
{
    float fadeFactor = clamp(1.0 - ((fs_in.timeSinceHit - fadeDelay) / timeToLive), 0.0, 1.0);
// This solution sucks but it's good enough until we have actual textures and then I might just remove the Color attribute completely
    if(useTexture) {
        FragColor = texture(diffuseTexture, fs_in.TextureCoords);
    } else {
        FragColor = vec4(fs_in.Color);
    }
    //FragColor.a *= fadeFactor;

} 