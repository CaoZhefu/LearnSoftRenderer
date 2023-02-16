#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "root_directory.h"
#include "platform/viewport.h"
#include "graphics/renderer.h"
#include "test/testModel.h"

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

    // mesh cube = TestModel::getTestCube();
    Shader_Nothing shader;
    mesh m;
    m.vertexs.push_back(vec3(0.5f, 0.5f, 0.5f));
    m.vertexs.push_back(vec3(0.5f, 0.f, 0.5f));
    m.vertexs.push_back(vec3(0.f, 0.f, 0.5f));
    m.facet_vert.push_back(0);
    m.facet_vert.push_back(1);
    m.facet_vert.push_back(2);

    r.shader = &shader;

    // main loop
    while(!v.shouldClose)
    {
        // render
        r.fill(color4(0, 0, 0, 255));
        r.drawMesh(m);

        // update viewport
        v.renderCopy(&r);
        v.updateBuffers();
        v.pollEvents();
    }

    v.destroy();
    return 0;
}