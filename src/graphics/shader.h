#pragma once

#include "math/mathUtils.h"
#include "texture.h"

class IShader
{
public:
    virtual void vert(vec3 inPos, vec4& outClipPos) {}
    virtual void frag(vec4 inClipPos, vec4& outColor) {}
};

class Shader_Phong : public IShader
{
public:
    mat4 model;
    mat4 view;
    mat4 persp;
    texture* diffuseTex;
    texture* normalTex;
    vec3 lightPos;
    vec3 lightColor;

    virtual void vert(vec3 inPos, vec4& outClipPos);
    virtual void frag(vec4 inClipPos, vec4& outColor);
};