#include <iostream>
#include "myMath.h"
#include "renderer.h"

int main()
{
    renderer r(300, 200);
    r.fill(vec4(255, 255, 255, 1.f));
    r.saveToFile("out.bmp");

#if defined(WIN32) || defined(_WIN32)
	system("mspaint out.bmp");
#endif

    return 0;
}