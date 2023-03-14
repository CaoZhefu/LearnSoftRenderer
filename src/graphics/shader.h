#pragma once

#include "math/mathUtils.h"
#include "texture.h"

struct vertexShaderIn
{
    vec3 vertex;
    vec2 uv;
};

struct vertexShaderOut
{
    vec4 pos;
    vec2 uv;
};

class IShader
{
public:
    virtual void vert(vertexShaderIn& in, vertexShaderOut& out) = 0;
    virtual vec4 frag(vertexShaderOut& in) = 0;
};

class Shader_Nothing : public IShader
{
    virtual void vert(vertexShaderIn& in, vertexShaderOut& out)
    {
        out.pos = vec4(in.vertex, 1);
        out.uv = in.uv;
    }

    virtual vec4 frag(vertexShaderOut& in)
    {
        return vec4(in.uv.u, in.uv.v, 0, 1);
    }
};


class Shader_Lambert : public IShader
{
public:
    mat4 model;
    mat4 view;
    mat4 perspective;

    vec4 lightPos;
    vec4 viewPos;

    vec4 specularColor = vec4(0.6f, 0.6f, 0.6f, 1.f);

    texture* diffuseTex = nullptr;
    texture* normalTex = nullptr;

    virtual void vert(vertexShaderIn& in, vertexShaderOut& out)
    {
        vec4 worldPos = model * vec4(in.vertex, 1);
        vec4 viewPos = view * worldPos;
        vec4 clipPos = perspective * viewPos;
        out.pos = clipPos;
        out.uv = in.uv;
    }

    virtual vec4 frag(vertexShaderOut& in)
    {
        vec3 diffuse;
        if(diffuseTex)
        {
            diffuse = diffuseTex->sample(in.uv).xyz();
        }

        vec3 lightDir = (lightPos - in.pos).xyz();
        lightDir.normalize();

        vec3 normal;
        if(normalTex)
        {
            normal = normalTex->sample(in.uv).xyz();
            normal = normal * 2.0f - 1.0f;
            normal.normalize();
        }

        float NL = clamp(lightDir * normal, 0.f, 1.f);

        vec3 viewDir = (viewPos - in.pos).xyz();
        viewDir.normalize();

        vec3 halfDir = (viewDir + lightDir) / 2.f;
        halfDir.normalize();

        float NH = clamp(normal * halfDir, 0.f, 1.f);
        NH = pow(NH, 64);

        return vec4(NL * diffuse, 1) + NH * specularColor;
    }
};