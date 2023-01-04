#include "texture.h"

void texture::loadFile(const string& path) {
    data = stbi_load(path.c_str(), &width, &height, &channelCnt, 0);

    if(!data)
    {
        std::cerr << "Texture load failed at path: " << path << std::endl;
    }
}

vec4 texture::sample(vec2 uv) {
    uv.x = frac(uv.x);
    uv.y = frac(uv.y);

    int x = clamp(int(width * uv.x), 0, width - 1);
    int y = clamp(int(height * uv.y), 0, height - 1);

    return get(x, y);
}

vec4 texture::get(int x, int y) {
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