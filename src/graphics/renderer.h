#pragma once

#include "math/mathUtils.h"
#include "mesh.h"
#include "shader.h"

#include <string>
#include <fstream>

struct camera
{
    vec3 pos;
    vec3 lookPoint;
    vec3 up;
};

class renderer
{
public:
    int width, height;
    unsigned char* frameBuffer;
    float* zBuffer;

    camera renderCam;

    bool render_frame;
    color4 frame_color;

    IShader* shader;

    renderer(int w, int h) {
        width = w;
        height = h;
        frameBuffer = new unsigned char[width * height * 3];
        zBuffer = new float[width * height];

        renderCam.pos = vec3(2.5f, 2.5f, 2.5f);
        renderCam.lookPoint = vec3(0.f, 0.f, 0.f);
        renderCam.up = vec3(0.f, 1.f, 0.f);

        render_frame = false;
        frame_color = color4(255, 255, 255, 255);
    }

    // 2D Draw
    void fill(const color4& color);
    void drawPixel(int x, int y, const color4& color);
    void drawLine(int x1, int y1, int x2, int y2, const color4& color);
    void drawTriangle_lineSweep(vec2 v1, vec2 v2, vec2 v3, const color4& color);
    void drawTriangle(vec2 v1, vec2 v2, vec2 v3, const color4& color);

    // 3D draw
    void drawMesh(const mesh& model);
private:
    bool drawPrimitive(std::vector<vertexShaderIn>& vsInContexts);

    // 判断一条边是不是三角形的左上边 (Top-Left Edge)
	inline bool IsTopLeft(const vec2i& a, const vec2i& b) {
		return ((a.y == b.y) && (a.x < b.x)) || (a.y > b.y);
	}

public:
    void filpFrameBuffer();
    void clearDepthBuffer();

    ~renderer(){
        delete[] frameBuffer;
        delete[] zBuffer;
    }
};