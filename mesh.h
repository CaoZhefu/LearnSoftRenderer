#pragma once

#include "MathUtils.h"
#include <vector>

using std::vector;
using std::string;

class texture
{
public:
    unsigned char* data;

    texture(const string& path)
    {

    }

    ~texture()
    {

    }
};

class mesh
{
public:
    vector<vec3> vertexs;
    vector<vec2> texcoords;
    vector<vec3> normals;

    vector<int> facet_vert;
    vector<int> facet_texcoord;
    vector<int> facet_norm;

    mesh(){}
    mesh(const string& filename);
};
