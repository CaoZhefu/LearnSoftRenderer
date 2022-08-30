#include "renderer.h"

void renderer::fill(const vec3& color) {
    for(int i = 0; i < width * height; ++i)
        frameBuffer[i] = color;
}

void renderer::drawPixel(int x, int y, const vec3& color){
    if(x >= 0 && x < width && y >= 0 && y < height)
        frameBuffer[width * y + x] = color;
}

void renderer::drawLine(int x1, int y1, int x2, int y2, const vec3& color) {
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

void renderer::drawTriangle_lineSweep(vec2 v1, vec2 v2, vec2 v3, const vec3& color) {
    // sort vertex by Y
    if(v1.y > v2.y) std::swap(v1, v2);
    if(v1.y > v3.y) std::swap(v1, v3);
    if(v2.y > v3.y) std::swap(v2, v3);
    int total_height = v3.y - v1.y;

    // draw bottom part
    int bottom_height = v2.y - v1.y + 1;
    for(int y = v1.y; y <= v2.y; ++y){
        float a1 = (float)(y - v1.y) / total_height;
        float a2 = (float)(y - v1.y) / bottom_height;
        vec2 A = v1 + (v3 - v1) * a1;
        vec2 B = v1 + (v2 - v1) * a2;
        if(A.x > B.x) std::swap(A, B);
        for(int i = A.x; i <= B.x; ++i)
            drawPixel(i, y, color);
    }

    // draw upper part
    int upper_height = v3.y - v2.y + 1;
    for(int y = v2.y; y <= v3.y; ++y){
        float a1 = (float)(y - v1.y) / total_height;
        float a2 = (float)(y - v2.y) / upper_height;
        vec2 A = v1 + (v3 - v1) * a1;
        vec2 B = v2 + (v3 - v2) * a2;
        if(A.x > B.x) std::swap(A, B);
        for(int i = A.x; i <= B.x; ++i)
            drawPixel(i, y, color);
    }
}

void renderer::drawTriangle(vec2 v1, vec2 v2, vec2 v3, const vec3& color) {
    vec2 bboxmin(width - 1, height - 1);
    vec2 bboxmax(0, 0);
    bboxmin.x = std::max(0.f, std::min(v1.x, std::min(v2.x, v3.x)));
    bboxmin.y = std::max(0.f, std::min(v1.y, std::min(v2.y, v3.y)));
    bboxmax.x = std::min((float)(width - 1), std::max(v1.x, std::max(v2.x, v3.x)));
    bboxmax.y = std::min((float)(height - 1), std::max(v1.y, std::max(v2.y, v3.y)));

    vec2 p;
    for(p.x = bboxmin.x; p.x <= bboxmax.x; p.x++){
        for(p.y = bboxmin.y; p.y <= bboxmax.y; p.y++){
            vec3 bc = barycentric(v1, v2, v3, p);
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            drawPixel(p.x, p.y, color);
        }
    }
}

void renderer::drawMesh(const mesh& model, IShader& shader) {
    // render per face
    for(int i = 0; i < model.faceNum(); ++i) {
        // 1. get face vertexs 
        vec3 originVerts[3];
        for(int j = 0; j < 3; ++j)
            originVerts[j] = model.getVertex(i, j);

        // 2. transform to clip coordinates
        vec4 clipPos[3];
        for(int j = 0; j < 3; ++j)
            shader.vert(originVerts[j], clipPos[j]);

        // 3. rasterize to screen, check zbuffer

        // 4. shading by frag shader
    }
}

void renderer::filpFrameBuffer() {
    int i = 0;
    int j = height - 1;
    while(j > i){
        for(int x = 0; x < width; ++x){
            std::swap(frameBuffer[x + width * i], frameBuffer[x + width * j]);
        }
        ++i; --j;
    }
}

void renderer::saveToBmp(const std::string& path) {
    unsigned char* data = new unsigned char[width * height * 3];
    for(int i = 0; i < width * height; ++i){
        data[i * 3 + 0] = (unsigned char)frameBuffer[i].x;
        data[i * 3 + 1] = (unsigned char)frameBuffer[i].y;
        data[i * 3 + 2] = (unsigned char)frameBuffer[i].z;
    }

    stbi_write_bmp(path.c_str(), width, height, 3, data);
    delete data;
}