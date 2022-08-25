#pragma once

#include "MathUtils.h"
#include "ThirdParty/stb_image_write.h"

#include <string>
#include <fstream>

class renderer
{
public:
    int width, height;
    vec3* frameBuffer;
    float* zBuffer;

    renderer(int w, int h) : width(w), height(h){
        frameBuffer = new vec3[w * h];
        zBuffer = new float[w * h];
    }

    void fill(const vec3& color);
    void drawPixel(int x, int y, const vec3& color);
    void drawLine(int x1, int y1, int x2, int y2, const vec3& color);
    void drawTriangle_lineSweep(vec2 v1, vec2 v2, vec2 v3, const vec3& color);
    void drawTriangle(vec2 v1, vec2 v2, vec2 v3, const vec3& color);
    void filpFrameBuffer();
    void saveToBmp(const std::string& path);

    ~renderer(){
        delete[] frameBuffer;
        delete[] zBuffer;
    }
};