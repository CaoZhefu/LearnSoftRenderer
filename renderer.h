#pragma once

#include "MathUtils.h"
#include "ThirdParty/stb_image_write.h"
#include "mesh.h"
#include "shader.h"

#include <string>
#include <fstream>

struct camera
{
    vec3 pos;
    vec3 front;
    vec3 up;
};

class renderer
{
public:
    int width, height;
    vec3* frameBuffer;
    float* zBuffer;

    camera renderCam;

    renderer(int w, int h) : width(w), height(h){
        frameBuffer = new vec3[w * h];
        zBuffer = new float[w * h];

        renderCam.pos = vec3(0.f, 0.f, 0.f);
        renderCam.front = vec3(0.f, 0.f, -1.f); // default point to -z
        renderCam.up = vec3(0.f, 1.f, 0.f); // default up
    }

    void fill(const vec3& color);
    void drawPixel(int x, int y, const vec3& color);
    void drawLine(int x1, int y1, int x2, int y2, const vec3& color);
    void drawTriangle_lineSweep(vec2 v1, vec2 v2, vec2 v3, const vec3& color);
    void drawTriangle(vec2 v1, vec2 v2, vec2 v3, const vec3& color);
    void drawMesh(const mesh& model, IShader& shader);
    void filpFrameBuffer();
    void saveToBmp(const std::string& path);

    ~renderer(){
        delete[] frameBuffer;
        delete[] zBuffer;
    }
};