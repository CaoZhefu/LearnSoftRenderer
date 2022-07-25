#include <iostream>
#include "myMath.h"
#include "renderer.h"

int main()
{
    renderer render(300, 200);
    
    for(int i = 0; i < render.width; ++i)
    {
        for(int j = 0; j < render.height; ++j)
        {
            float r = (float)i / (float)render.width * 255.0f;
            float g = (float)j / (float)render.height * 255.0f;
            render.drawPixel(i, j, vec4(r, g, 0, 1));
        }
    }

    render.saveToFile("out.bmp");

#if defined(WIN32) || defined(_WIN32)
	system("mspaint out.bmp");
#endif

    return 0;
}