#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


in VS_OUT {
    vec3 Color;
} gs_in[];

out GS_OUT {
    vec3 Color;
} gs_out;


uniform float explosionTime;
uniform vec3 explosionOrigin;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
    vec3 triangleCenter = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz) / 3.0;
    vec3 explosionVector = triangleCenter - explosionOrigin;

    float expRadius = explosionTime * 1;
    float distToShockWave = length(explosionVector) - expRadius;


    vec3 offset = (-distToShockWave/2) * normalize(explosionVector) * max(0, -sign(distToShockWave));

    for (int i = 0; i < 3; ++i)
    {
        vec3 newWorldPos = gl_in[i].gl_Position.xyz + offset;
        gl_Position = uProjectionMatrix * uViewMatrix * vec4(newWorldPos, 1.0);
        gs_out.Color = gs_in[i].Color;
        EmitVertex();
    }
    EndPrimitive();
}