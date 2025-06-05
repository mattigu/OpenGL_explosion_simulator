#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


in VS_OUT {
    vec4 Color;
    vec2 TextureCoords;
    vec3 WorldPos;
} gs_in[];

out GS_OUT {
    vec4 Color;
    vec2 TextureCoords;
    float timeSinceHit;
} gs_out;

uniform bool useInstancing;

uniform float explosionTime;
uniform vec3 explosionOrigin;
uniform float explosionStrength;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;


const float G = 10.0;
const float ground = -10.0;
const float rampTime = 0.2; // Time to reach max velocity after being hit by the explosion.
const float baseAngularVelocity = 2.0;
const float baseAngularAccel = 0.4;

float expVelocity = 5.0; 

float rand(float seed) {
    return fract(sin(seed) * 43758.5453);
}

float randRange(float seed, float low, float high) {
    float diff = high - low;
    float rng = rand(seed) * diff + low;
    return rng;
}

mat3 rotationX(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return mat3(
        1, 0, 0,
        0, c, -s,
        0, s, c
    );
}

mat3 rotationZ(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return mat3(
        c, -s, 0,
        s, c, 0,
        0, 0, 1
    );
}

mat3 rotationY(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return mat3(
        c,  0.0,  s,
        0.0, 1.0, 0.0,
       -s,  0.0,  c);}

vec3 calculateOffset(vec3 velocity, vec3 point, float time)
{
    float xOffset = velocity.x * time;
    float yOffset = velocity.y * time - 0.5 * G * time*time;
    float zOffset = velocity.z * time;

    yOffset = max(ground, point.y + yOffset) - point.y; // Clip to ground

    vec3 offset = vec3(xOffset, yOffset, zOffset);
    
    return offset;
}

//vec3 rotatePoint (vec3 point, vec3 triangleCenter, vec3 expDir, float time, float id)
//{ 
//    float angularVelocity = baseAngularVelocity * (rand(id)*2 - 1);
//    float angularAcceleration = -sign(angularVelocity) * baseAngularAccel;
//
//    float stopTime = abs(angularVelocity / angularAcceleration);
//    float t = clamp(time, 0.0, stopTime);
//
//    float angle = angularVelocity * t + 0.5 * angularAcceleration * t * t;      
//
//    vec3 p = point - triangleCenter; // translate for rotation
//
//    mat3 rotation = rotationZ(angle) * rotationZ(angle) * rotationX(angle);
//
//    vec3 rotatedPoint = rotation * p + triangleCenter;
//
//    return rotatedPoint;
//}

//This version has unique velocities per angle, but is significantly less performant. 
//One axis could be removed without much visual loss though.
vec3 rotatePoint (vec3 point, vec3 triangleCenter, vec3 expDir, float time, float id)
{ 
    vec3 axisX = vec3(1.0, 0.0, 0.0);
    vec3 axisY = vec3(0.0, 1.0, 0.0);
    vec3 axisZ = vec3(0.0, 0.0, 1.0);

    float angleXFactor = length(cross(axisX, expDir)) * randRange(id, 0.8, 1.2);
    float angleYFactor = length(cross(axisY, expDir)) * randRange(id, 0.8, 1.2);
    float angleZFactor = length(cross(axisZ, expDir)) * randRange(id, 0.8, 1.2);

    float baseAngVelX = baseAngularVelocity * angleXFactor;
    float baseAngVelY = baseAngularVelocity * angleYFactor;
    float baseAngVelZ = baseAngularVelocity * angleZFactor;

    float stopTimeX = abs(baseAngVelX / baseAngularAccel);
    float stopTimeY = abs(baseAngVelY / baseAngularAccel);
    float stopTimeZ = abs(baseAngVelZ / baseAngularAccel);

    float tX = clamp(time, 0.0, stopTimeX);
    float tY = clamp(time, 0.0, stopTimeY);
    float tZ = clamp(time, 0.0, stopTimeZ);

    // Calculate angles with kinematic formula
    float angleX = baseAngVelX * tX + 0.5 * (-sign(baseAngVelX) * baseAngularAccel) * tX * tX;
    float angleY = baseAngVelY * tY + 0.5 * (-sign(baseAngVelY) * baseAngularAccel) * tY * tY;
    float angleZ = baseAngVelZ * tZ + 0.5 * (-sign(baseAngVelZ) * baseAngularAccel) * tZ * tZ;

    // Translate to 0,0,0 for rotation
    vec3 p = point - triangleCenter;

    mat3 rotation = rotationX(angleX) * rotationY(angleY) * rotationZ(angleZ);

    vec3 rotatedPoint = rotation * p + triangleCenter;
    return rotatedPoint;
}

void main()
{
    // First point of the primitive as seed.
    float seed = fract(dot(gs_in[0].WorldPos, vec3(7.198, 3.233, 1.53)));

    vec3 triangleCenter = (gs_in[0].WorldPos + gs_in[1].WorldPos + gs_in[2].WorldPos) / 3.0;
    vec3 expVector = triangleCenter - explosionOrigin;

    float expRadius = explosionTime * expVelocity;
    float distToShockWave = length(expVector) - expRadius; // Distance of triangle center to shockwave

    float timeSinceHit = abs(min(0, distToShockWave/expVelocity));

    vec3 direction = normalize(expVector);
    vec3 randomNudge = vec3(randRange(seed, 0.8, 1.2), randRange(seed + 1, 0.8, 1.2), randRange(seed + 2, 0.8, 1.2));

    direction = normalize(direction * randomNudge);

    float ramp = smoothstep(0.0, rampTime, timeSinceHit);

    float randomVelocityMult = randRange(seed, 0.9, 1.1);
    vec3 velocity = direction * ramp * randomVelocityMult * explosionStrength; 
    vec3 offset = calculateOffset(velocity, triangleCenter, timeSinceHit);

    for (int i = 0; i < 3; ++i)
    {
        vec3 rotated = rotatePoint(gs_in[i].WorldPos, triangleCenter, direction, timeSinceHit, seed);
        vec3 newWorldPos = rotated + offset;
        gl_Position = uProjectionMatrix * uViewMatrix * vec4(newWorldPos, 1.0);
        gs_out.Color = gs_in[i].Color;
        gs_out.TextureCoords = gs_in[i].TextureCoords;
        gs_out.timeSinceHit = timeSinceHit;
        EmitVertex();
    }
    EndPrimitive();
}