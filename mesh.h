#pragma once

#include "MathUtils.h"
#include <vector>
#include "ThirdParty/stb_image.h"

using std::vector;
using std::string;

class texture
{
public:
    unsigned char* data;
    int width, height, channelCnt;

    texture() {}
    texture(const string& path) { loadFile(path); }

    void loadFile(const string& path);
    vec4 sample(vec2 uv);
    vec4 get(int x, int y);

    ~texture() { stbi_image_free(data); }
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

    int faceNum() const;
    vec3 getVertex(const int i) const;
    vec3 getVertex(const int face_idx, const int offset) const;
    vec2 getTexcoord(const int face_idx, const int offset) const;
    vec3 getNormal(const int face_idx, const int offset) const;
};
