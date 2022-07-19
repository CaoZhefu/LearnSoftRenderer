#include "myMath.h"

class renderer
{
public:
    int width, height;
    vec4** frameBuffer;
    float** zBuffer;

    renderer(int w, int h) : width(w), height(h){
        frameBuffer = new vec4*[w];
        zBuffer = new float*[w];

        for(int i = 0; i < w; ++i){
            frameBuffer[i] = new vec4[h];
            zBuffer[i] = new float[h];
        }
    }

    void drawPixel(int x, int y, vec4& color){
        if(x >= 0 && x < width && y >= 0 && y < height)
            frameBuffer[x][y] = color;
    }

    // 保存为bmp文件
    void saveToFile(const char* path){

    }

    ~renderer(){
        for(int i = 0; i < width; ++i){
            delete[] frameBuffer[i];
            delete[] zBuffer[i];
        }

        delete[] frameBuffer;
        delete[] zBuffer;
    }
};