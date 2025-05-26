#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


in VS_OUT {
    vec4 Color;
    vec2 TextureCoords;
} gs_in[];

out GS_OUT {
    vec4 Color;
    vec2 TextureCoords;
} gs_out;


uniform float explosionTime;
uniform vec3 explosionOrigin;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;


const float G = 10.0;
const float ground = -10.0;

float expVelocity = 5.0; // How fast the explosion radius increases per second
// Should probably be a uniform, but it currently it's equivalent to explosionTime anyway

vec3 calculateNewCoordinates(vec3 velocity, vec3 point, float time)
{
    float xOffset = velocity.x * time;
    float yOffset = velocity.y * time - 0.5 * G * time*time;
    float zOffset = velocity.z * time;

    yOffset = max(ground, point.y + yOffset) - point.y; // Clip to ground

    vec3 offset = vec3(xOffset, yOffset, zOffset);
    
    return offset;
}


void main()
{
    vec3 triangleCenter = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz) / 3.0;
    vec3 expVector = triangleCenter - explosionOrigin;

    float expRadius = explosionTime * expVelocity;
    float distToShockWave = length(expVector) - expRadius; // Distance of triangle center to shockwave

    float timeSinceHit = abs(min(0, distToShockWave/expVelocity));

    vec3 velocity = normalize(expVector) * max(0, -sign(distToShockWave)) * 10.0;
    vec3 offset = calculateNewCoordinates(velocity, triangleCenter, timeSinceHit);

    for (int i = 0; i < 3; ++i)
    {
        vec3 newWorldPos = gl_in[i].gl_Position.xyz + offset;
        gl_Position = uProjectionMatrix * uViewMatrix * vec4(newWorldPos, 1.0);
        gs_out.Color = gs_in[i].Color;
        gs_out.TextureCoords = gs_in[i].TextureCoords;
        EmitVertex();
    }
    EndPrimitive();
}