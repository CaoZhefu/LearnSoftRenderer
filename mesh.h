#pragma once

#include <vector>
#include "MathUtils.h"
#include "ThirdParty/stb_image.h"

using std::vector;
using std::string;

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

    int faceNum() const;
    vec3 getVertex(const int i) const;
    vec3 getVertex(const int face_idx, const int offset) const;
    vec2 getTexcoord(const int face_idx, const int offset) const;
    vec3 getNormal(const int face_idx, const int offset) const;
};
