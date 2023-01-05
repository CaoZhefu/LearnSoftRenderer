#pragma once

#include<string>
#include "math/mathUtils.h"
#include "stb_image.h"

using std::string;

class texture
{
public:
    unsigned char* data;
    int width, height, channelCnt;
    bool bLoadFromFile;

    texture() {}
    texture(const string& path);
    texture(int _width, int _height, int _channelCnt);

    void loadFile(const string& path);
    vec4 sample(vec2 uv);
    vec4 get(int x, int y);
    void clearData();

    ~texture() { clearData(); }
};