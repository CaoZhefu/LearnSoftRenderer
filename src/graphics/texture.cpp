#include "texture.h"

texture::texture(const string &path)
{
    loadFile(path);
}

texture::texture(int _width, int _height, int _channelCnt)
{
    if(_width <= 0 || _height <= 0 || _channelCnt <= 0 || _channelCnt > 4)
    {
        std::cerr << "texture constructor error : invalid arguments" << std::endl;
    }

    this->width = _width;
    this->height = _height;
    this->channelCnt = _channelCnt;
    int size = _width * _height * _channelCnt;
    this->data = (unsigned char*)malloc(size * sizeof(unsigned char));
    bLoadFromFile = false;
}

void texture::loadFile(const string &path)
{
    data = stbi_load(path.c_str(), &width, &height, &channelCnt, 0);

    if(!data)
    {
        std::cerr << "Texture load failed at path: " << path << std::endl;
    }
    else
    {
        bLoadFromFile = true;
    }
}

vec4 texture::sample(vec2 uv) {
    uv.x = frac(uv.x);
    uv.y = frac(uv.y);

    int x = clamp((int)(width * uv.x), 0, width - 1);
    int y = clamp((int)(height * uv.y), 0, height - 1);

    return get(x, y);
}

vec4 texture::get(int x, int y) {
    vec4 ret;
    if(!data || x < 0 || y < 0 || x >= width || y >= height)
        return ret;

    int idx = y * height + x;

    // Gray
    if(channelCnt == 1) {    
        ret.r = color01From255(data[idx]);
    }
    // Gray Alpha
    else if(channelCnt == 2) {
        ret.r = color01From255(data[idx * 2]);
        ret.a = color01From255(data[idx * 2 + 1]);
    }
    // RGB
    else if(channelCnt == 3) {
        ret.r = color01From255(data[idx * 3]);
        ret.g = color01From255(data[idx * 3 + 1]);
        ret.b = color01From255(data[idx * 3 + 2]);
    }
    // RGBA
    else if(channelCnt == 4) {
        ret.r = color01From255(data[idx * 4]);
        ret.g = color01From255(data[idx * 4 + 1]);
        ret.b = color01From255(data[idx * 4 + 2]);
        ret.a = color01From255(data[idx * 4 + 3]);
    }
    
    return ret;
}

void texture::clearData()
{
    if(data)
    {
        bLoadFromFile ? stbi_image_free(data) : free(data);
        data = nullptr;
    }
}