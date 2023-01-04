#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "root_directory.h"
#include "platform/viewport.h"

int main()
{
    viewport v;
    v.init(800, 600, "SoftRenderer");
    while(!v.shouldClose())
    {
        // main loop
    }

    v.destroy();

//     renderer render(500, 500);
//     render.render_frame = true;
//     mesh floorMesh(string(root_dir) + "/obj/floor.obj");
//     Shader_Phong shader;

//     shader.model = getIdentityMatrix();
//     shader.view = lookat(render.renderCam.pos, render.renderCam.lookPoint, render.renderCam.up);
//     shader.persp = getPerspectiveMatrix(3.1415926f * 0.6f, (float)render.width / (float)render.height, 1.0, 1000.f);
//     render.drawMesh(floorMesh, shader); 

//     //render.filpFrameBuffer();
//     render.saveToBmp("out.bmp");

// #if defined(WIN32) || defined(_WIN32)
// 	system("mspaint out.bmp");
// #endif

    return 0;
}