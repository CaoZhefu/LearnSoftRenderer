#include <iostream>

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "renderer.h"
#include "mesh.h"
#include "shader.h"

int main()
{
    renderer render(500, 500);
    mesh floorMesh("../../obj/floor.obj");
    Shader_Phong shader;

    //shader.model = ...
    //shader.persp = ...
    //render.drawMesh(floorMesh, shader); 

    render.filpFrameBuffer();
    render.saveToBmp("out.bmp");

#if defined(WIN32) || defined(_WIN32)
	system("mspaint out.bmp");
#endif

    return 0;
}