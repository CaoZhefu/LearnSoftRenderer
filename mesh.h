#pragma once

#include "myMath.h"
#include <vector>

using std::vector;

struct vertex
{
    vec4 pos;
    vec4 normal;
    vec4 uv;
};

struct mesh
{
    vector<vertex> vertexs;
};
