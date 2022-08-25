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

    texture(const string& path) {
        loadFile(path);
    }

    void loadFile(const string& path) {
        data = stbi_load(path.c_str(), &width, &height, &channelCnt, 0);

        if(!data)
        {
            std::cerr << "Texture load failed at path: " << path << std::endl;
        }
    }

    ~texture() {
        delete data;
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
