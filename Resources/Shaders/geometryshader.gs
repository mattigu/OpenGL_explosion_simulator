#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


in VS_OUT {
    vec3 vColor;
} gs_in[];

out vec3 gColor;

uniform float explosionTime;
uniform vec3 explosionPoint;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
    vec3 triangleCenter = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz) / 3.0;
    vec3 explosionVector = normalize(triangleCenter - explosionPoint);
    vec3 offset = explosionTime * explosionVector;


    for (int i = 0; i < 3; ++i)
    {
        vec3 newWorldPos = gl_in[i].gl_Position.xyz + offset;
        gl_Position = uProjectionMatrix * uViewMatrix * vec4(newWorldPos, 1.0);
        gColor = gs_in[i].vColor;
        EmitVertex();
    }
    EndPrimitive();
}