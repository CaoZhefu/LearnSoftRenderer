#pragma once

#include<string>
#include "math/MathUtils.h"
#include "stb_image.h"

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