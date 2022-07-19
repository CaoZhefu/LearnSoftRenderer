#pragma once

#include "myMath.h"

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#include "stb_image_write.h"
#include <string>
#include <fstream>

class renderer
{
public:
    int width, height;
    vec4* frameBuffer;
    float* zBuffer;

    renderer(int w, int h) : width(w), height(h){
        frameBuffer = new vec4[w * h];
        zBuffer = new float[w * h];
    }

    void drawPixel(int x, int y, const vec4& color){
        if(x >= 0 && x < width && y >= 0 && y < height)
            frameBuffer[width * y + x] = color;
    }

    void fill(const vec4& color){
        for(int i = 0; i < width * height; ++i)
            frameBuffer[i] = color;
    }

    // 保存为文件
    void saveToFile(const std::string& path){
        unsigned char* data = new unsigned char[width * height * 3];
        for(int i = 0; i < width * height; ++i){
            data[i * 3 + 0] = frameBuffer[i].x;
            data[i * 3 + 1] = frameBuffer[i].y;
            data[i * 3 + 2] = frameBuffer[i].z;
        }

        stbi_write_bmp(path.c_str(), width, height, 3, data);
        delete[] data;
    }

    ~renderer(){
        delete[] frameBuffer;
        delete[] zBuffer;
    }
};