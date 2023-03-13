#include "renderer.h"

void renderer::fill(const color4& color) {
    for(int i = 0; i < width * height; ++i)
    {
        frameBuffer[i * 3 + 0] = color.r;
        frameBuffer[i * 3 + 1] = color.g;
        frameBuffer[i * 3 + 2] = color.b;
    }
}

void renderer::drawPixel(int x, int y, const color4& color){
    if(x >= 0 && x < width && y >= 0 && y < height)
    {
        int index = width * y + x;
        frameBuffer[index * 3 + 0] = color.r;
        frameBuffer[index * 3 + 1] = color.g;
        frameBuffer[index * 3 + 2] = color.b;
    }  
}

void renderer::drawLine(int x1, int y1, int x2, int y2, const color4& color) {
    // std::cout << "drawLine :(" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")" << std::endl;

    bool steep = false;
    // traverse by X or Y
    if(std::abs(x2 - x1) < std::abs(y2 - y1))
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }

    // traverse from smaller value
    if(x2 < x1)
    {
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
    for(int x = x1; x <= x2; ++x)
    {
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

void renderer::drawTriangle_lineSweep(vec2 v1, vec2 v2, vec2 v3, const color4& color) {
    // sort vertex by Y
    if(v1.y > v2.y) std::swap(v1, v2);
    if(v1.y > v3.y) std::swap(v1, v3);
    if(v2.y > v3.y) std::swap(v2, v3);
    int total_height = v3.y - v1.y;

    // draw bottom part
    int bottom_height = v2.y - v1.y + 1;
    for(int y = v1.y; y <= v2.y; ++y)
    {
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
    for(int y = v2.y; y <= v3.y; ++y)
    {
        float a1 = (float)(y - v1.y) / total_height;
        float a2 = (float)(y - v2.y) / upper_height;
        vec2 A = v1 + (v3 - v1) * a1;
        vec2 B = v2 + (v3 - v2) * a2;
        if(A.x > B.x) std::swap(A, B);
        for(int i = A.x; i <= B.x; ++i)
            drawPixel(i, y, color);
    }
}

void renderer::drawTriangle(vec2 v1, vec2 v2, vec2 v3, const color4& color) {
    vec2 bboxmin(width - 1, height - 1);
    vec2 bboxmax(0, 0);
    bboxmin.x = std::max(0.f, std::min(v1.x, std::min(v2.x, v3.x)));
    bboxmin.y = std::max(0.f, std::min(v1.y, std::min(v2.y, v3.y)));
    bboxmax.x = std::min((float)(width - 1), std::max(v1.x, std::max(v2.x, v3.x)));
    bboxmax.y = std::min((float)(height - 1), std::max(v1.y, std::max(v2.y, v3.y)));

    vec2 p;
    for(p.x = bboxmin.x; p.x <= bboxmax.x; p.x++) 
    {
        for(p.y = bboxmin.y; p.y <= bboxmax.y; p.y++) 
        {
            vec3 bc = barycentric(v1, v2, v3, p);
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            drawPixel((int)(p.x + 0.5f), (int)(p.y + 0.5f), color);
        }
    }
}

void renderer::drawMesh(const mesh& model) {
    if(shader == nullptr)
    {
        std::cerr << "renderer::drawMesh Failed, Shader is Null!" << std::endl;
        return;
    }

    for(int i = 0; i < model.faceNum(); ++i) 
    {
        // draw each primitive
        std::vector<vertexShaderIn> contexts(3);
        for(int j = 0; j < 3; ++j) {
            contexts[j].vertex = model.getVertex(i, j);
            contexts[j].uv = model.getTexcoord(i, j);
        }
        drawPrimitive(contexts);
    }
}

bool renderer::drawPrimitive(std::vector<vertexShaderIn> &vsInContexts)
{
    if(vsInContexts.size() != 3)
        return false;

    // run vertex shader
    std::vector<vertexShaderOut> vsOutContexts(3);
    for(int i = 0; i < 3; ++i)
    {
        shader->vert(vsInContexts[i], vsOutContexts[i]);
    }

    // clip
    float reverseW[3];
    for(int i = 0; i < 3; ++i)
    {
        vec4& pos = vsOutContexts[i].pos;
        float w = pos.w;
        if(pos.w == 0.f || pos.z < 0.f || pos.z > w || pos.x < -w || pos.x > w || pos.y < -w || pos.y > w)
        {
            // discard primitive
            return false;
        }
        // 透视除法
        reverseW[i] = 1.0f / w;
        pos = pos * reverseW[i];
    }
    
    // transfer to viewport pos
    vec2 viewportPos[3];
    vec2i viewportPosInt[3];
    for(int i = 0; i < 3; ++i)
    {
        viewportPos[i].x = (vsOutContexts[i].pos.x + 1.f) * (float)width * 0.5f;
        viewportPos[i].y = (1.f - vsOutContexts[i].pos.y) * (float)height * 0.5f;
        viewportPosInt[i].x = (int)round(viewportPos[i].x);
        viewportPosInt[i].y = (int)round(viewportPos[i].y);
    }

    // render as frame
    if(render_frame)
    {
        drawLine(viewportPosInt[0].x, viewportPosInt[0].y, viewportPosInt[1].x, viewportPosInt[1].y, frame_color);
        drawLine(viewportPosInt[0].x, viewportPosInt[0].y, viewportPosInt[2].x, viewportPosInt[2].y, frame_color);
        drawLine(viewportPosInt[2].x, viewportPosInt[2].y, viewportPosInt[1].x, viewportPosInt[1].y, frame_color);
        return true;
    }

    // 求外接矩形
    int min_x = width - 1, max_x = 0, min_y = height - 1, max_y = 0;
    for(int i = 0; i < 3; ++i)
    {
        min_x = min_x <= viewportPosInt[i].x ? min_x : viewportPosInt[i].x;
        max_x = max_x >= viewportPosInt[i].x ? max_x : viewportPosInt[i].x;
        min_y = min_y <= viewportPosInt[i].y ? min_y : viewportPosInt[i].y;
        max_y = max_y >= viewportPosInt[i].y ? max_y : viewportPosInt[i].y;
    }

    vec2i& p0 = viewportPosInt[0];
    vec2i& p1 = viewportPosInt[1];
    vec2i& p2 = viewportPosInt[2];
    
    // 求面积
    float area = abs(cross(p1 - p0, p2 - p0));
    if(area <= 0) return false;

    // 遍历外接矩形
    for(int y = min_y; y <= max_y; ++y)
    {
        for(int x = min_x; x <= max_x; ++x)
        {
            vec2 pixelCenter((float)x + 0.5f, (float)y + 0.5f);

            // 当前像素点到三角形三个顶点的向量
            vec2 v0 = viewportPos[0] - pixelCenter;
            vec2 v1 = viewportPos[1] - pixelCenter;
            vec2 v2 = viewportPos[2] - pixelCenter;

            // 叉乘判断
            int cross01 = (x - p0.x) * (p1.y - p0.y) - (y - p0.y) * (p1.x - p0.x);
            int cross12 = (x - p1.x) * (p2.y - p1.y) - (y - p1.y) * (p2.x - p1.x);
            int cross20 = (x - p2.x) * (p0.y - p2.y) - (y - p2.y) * (p0.x - p2.x);
            
            bool bIn = (cross01 > 0) == (cross12 > 0) && (cross01 > 0) == (cross20 > 0) && (cross12 > 0) == (cross20 > 0);
            if(!bIn)
                continue;

            // 内部三个三角形面积
            float area_a = abs(cross(v1, v2));  // px-p1-p2
            float area_b = abs(cross(v2, v0));  // px-p2-p0
            float area_c = abs(cross(v0, v1));  // px-p0-p1
            float area_all = area_a + area_b + area_c;

            if(area_all <= 0.f)
                continue;

            // a + b +c = 1 
            float a = area_a / area_all;
            float b = area_b / area_all;
            float c = area_c / area_all;

            // 插值算当前点的 1/w
            float rhw = reverseW[0] * a + reverseW[1] * b + reverseW[2] * c;

            // Depth Buffer Test and Write
            if(rhw < zBuffer[y * width + x]) 
                continue;
            zBuffer[y * width + x] = rhw;

            // 当前像素w
            float w = rhw != 0.f ? 1.0f / rhw : 1.0f;

            // 插值系数 除以各自顶点的w后进行屏幕空间插值再乘以当前w
            float c0 = reverseW[0] * a * w;
            float c1 = reverseW[1] * b * w;
            float c2 = reverseW[2] * c * w;

            // Prepare fragment shader input
            vertexShaderOut fragmentShaderIn;
            fragmentShaderIn.uv = vsOutContexts[0].uv * c0 + vsOutContexts[1].uv * c1 + vsOutContexts[2].uv * c2;

            // run pixel shader
            vec4 color = shader->frag(fragmentShaderIn);
            color4 finalColor = colorFromVec01(color);

            drawPixel(x, y, finalColor);
        }
    }
    
    return true;
}

void renderer::filpFrameBuffer() {
    int i = 0;
    int j = height - 1;
    while(j > i)
    {
        for(int x = 0; x < width; ++x)
        {
            std::swap(frameBuffer[x + width * i], frameBuffer[x + width * j]);
        }
        ++i; --j;
    }
}

void renderer::clearDepthBuffer()
{
    for(int i = 0; i < width * height; ++i)
        zBuffer[i] = 0.0f;
}