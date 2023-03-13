#pragma once

#include "math/mathUtils.h"
#include "texture.h"

struct vertexShaderIn
{
    vec3 vertex;
    // vec3 normal;
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

    virtual void vert(vertexShaderIn& in, vertexShaderOut& out)
    {
        std::cout << "vert Shader start, input vertex " << in.vertex << std::endl;
        vec4 worldPos = model * vec4(in.vertex, 1);
        std::cout << "world Pos : " << worldPos << std::endl;
        vec4 viewPos = view * worldPos;
        std::cout << "view Pos : " << viewPos << std::endl;
        vec4 clipPos = perspective * viewPos;
        std::cout << "clip Pos : " << clipPos << std::endl;
        out.pos = clipPos;
        out.uv = in.uv;
    }

    virtual vec4 frag(vertexShaderOut& in)
    {
        return vec4(in.uv.u, in.uv.v, 0, 1);
    }
};