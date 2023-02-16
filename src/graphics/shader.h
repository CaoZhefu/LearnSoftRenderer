#pragma once

#include "math/mathUtils.h"
#include "texture.h"

struct vertexShaderIn
{
    vec3 vertex;
    // vec3 normal;
    // vec2 uv;
};

struct vertexShaderOut
{
    vec4 pos;
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
    }

    virtual vec4 frag(vertexShaderOut& in)
    {
        return vec4(1, 1, 1, 1);
    }
};