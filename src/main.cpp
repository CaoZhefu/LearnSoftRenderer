#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "root_directory.h"
#include "platform/viewport.h"
#include "graphics/renderer.h"

static int SCREEN_WIDTH = 800;
static int SCREEN_HEIGHT = 600;

int main()
{
    viewport v;
    if(!v.init(SCREEN_WIDTH, SCREEN_HEIGHT, "SoftRenderer"))
    {
        std::cerr << "Init Viewport Failed" << std::endl;
        return -1;
    }

    renderer r(v.width, v.height);

    // main loop
    while(!v.shouldClose)
    {
        // render
        r.fill(vec3(0, 0, 0));
        r.drawLine(0, 0, 100, 200, vec3(255, 0, 0));

        // update viewport
        v.renderCopy(&r);
        v.updateBuffers();
        v.pollEvents();
    }

    v.destroy();
    return 0;
}