#pragma once

#include "MathUtils.h"

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

    void fill(const vec4& color){
        for(int i = 0; i < width * height; ++i)
            frameBuffer[i] = color;
    }

    void drawPixel(int x, int y, const vec4& color){
        if(x >= 0 && x < width && y >= 0 && y < height)
            frameBuffer[width * y + x] = color;
    }

    void drawLine(int x1, int y1, int x2, int y2, const vec4& color){
        bool steep = false;
        // traverse by X or Y
        if(std::abs(x2 - x1) < std::abs(y2 - y1)){
            std::swap(x1, y1);
            std::swap(x2, y2);
            steep = true;
        }

        // traverse from smaller value
        if(x2 < x1){
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        int dx = x2 - x1;
        int dy = y2 - y1;
        // float de = std::abs(dy / float(dx));
        // float e = 0;
        int de2 = std::abs(dy) * 2;
        int e2 = 0;
        int y = y1;
        for(int x = x1; x <= x2; ++x){
            (steep ? drawPixel(y, x, color) : drawPixel(x, y, color));
            // e += de;
            // if(e > 0.5f){
            //     y += (y2 > y1 ? 1 : -1);
            //     e -= 1.f;
            // }
            e2 += de2;
            if(e2 > dx){
                y += (y2 > y1 ? 1 : -1);
                e2 -= dx*2;
            }
        }
    }

    // 保存为文件
    void saveToBmp(const std::string& path){
        unsigned char* data = new unsigned char[width * height * 3];
        for(int i = 0; i < width * height; ++i){
            data[i * 3 + 0] = (unsigned char)frameBuffer[i][0];
            data[i * 3 + 1] = (unsigned char)frameBuffer[i][1];
            data[i * 3 + 2] = (unsigned char)frameBuffer[i][2];
        }

        stbi_write_bmp(path.c_str(), width, height, 3, data);
        delete data;
    }

    ~renderer(){
        delete[] frameBuffer;
        delete[] zBuffer;
    }
};