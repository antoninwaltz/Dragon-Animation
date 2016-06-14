#version 120

// FIXME

attribute vec3 Position;
attribute vec3 Normal;
attribute mat4 BoneTransform[4];
attribute float Weights[4];

varying vec2 TexCoord0;
varying vec3 Normal0;
varying vec3 WorldPos0;

const int MAX_BONES = 100;

uniform mat4 gWVP;
uniform mat4 gWorld;
uniform mat4 gBones[MAX_BONES];

void main()
{
    mat4 Transform = BoneTransform[0] * Weights[0];
    Transform     += BoneTransform[1] * Weights[1];
    Transform     += BoneTransform[2] * Weights[2];
    Transform     += BoneTransform[3] * Weights[3];

    vec4 PosL    = Transform * vec4(Position, 1.0);
    gl_Position  = gWVP * PosL;
    vec4 NormalL = Transform * vec4(Normal, 0.0);
    Normal0      = (gWorld * NormalL).xyz;
    WorldPos0    = (gWorld * PosL).xyz;
}

