#include <iostream>
#include <iomanip>
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

    mesh cube = TestModel::getTestCube();
    Shader_Lambert shader;

    r.shader = &shader;
    // r.render_frame = true;

    // set shader variable
    shader.model = getIdentityMatrix();

    // 相机空间z轴指向屏幕外，-z轴指向屏幕内
    shader.view = getViewMatrix(r.renderCam.pos, r.renderCam.lookPoint, r.renderCam.up);
    shader.perspective = getPerspectiveMatrix(45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.f);

    r.clearDepthBuffer();
    r.fill(color4(0, 0, 0, 255));
    r.drawMesh(cube);

    while(!v.shouldClose)
    {
        // update viewport
        v.renderCopy(&r);
        v.updateBuffers();
        v.pollEvents();
    }

    v.destroy();
    return 0;
}