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

    vec4 sample(vec2 uv) {
        uv.x = frac(uv.x);
        uv.y = frac(uv.y);

        int x = (int)(width * uv.x);
        int y = (int)(height * uv.y);
    
        return get(x, y);
    }

    vec4 get(int x, int y) {
        vec4 ret;
        if(!data || x < 0 || y < 0 || x >= width || y >= height)
            return ret;

        int idx = y * height + x;

        // Gray
        if(channelCnt == 1) {    
            ret[0] = (float)data[idx];
        }
        // Gray Alpha
        else if(channelCnt == 2) {
            ret[0] = (float)data[idx * 2];
            ret[3] = (float)data[idx * 2 + 1];
        }
        // RGB
        else if(channelCnt == 3) {
            ret[0] = (float)data[idx * 3];
            ret[1] = (float)data[idx * 3 + 1];
            ret[2] = (float)data[idx * 3 + 2];
        }
        // RGBA
        else if(channelCnt == 4) {
            ret[0] = (float)data[idx * 4];
            ret[1] = (float)data[idx * 4 + 1];
            ret[2] = (float)data[idx * 4 + 2];
            ret[3] = (float)data[idx * 4 + 3];
        }

        return ret;
    }

    ~texture() {
        stbi_image_free(data);
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
