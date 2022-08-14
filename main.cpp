#include <iostream>
#include "renderer.h"
#include "MathUtils.h"

int main()
{
    vec4 v;
    v[0] = 2.f;
    v[1] = 3.f;
    v[2] = 4.f;
    v[3] = 1.f;

    mat4 m = mat4::get_identity();
    m[0][3] = 2.f;
    m[1][3] = 3.f;
    m[2][3] = 1.f;

    std::cout << m * v << std::endl;

//     renderer render(300, 200);

//     render.drawLine(80, 40, 13, 20, vec4(255.f, 255.f, 255.f, 1.f));
//     render.saveToBmp("out.bmp");

// #if defined(WIN32) || defined(_WIN32)
// 	system("mspaint out.bmp");
// #endif

    return 0;
}