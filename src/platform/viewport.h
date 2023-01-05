#pragma once

#include <string>
#include <windows.h>
#include "graphics/texture.h"
#include "graphics/renderer.h"

class viewport
{
public:
    viewport();

    int width, height;
    bool shouldClose;

    bool init(int _width, int _height, const char* _title);
    void destroy();

    void renderCopy(renderer* r);
    void updateBuffers();
    void pollEvents();

private:
    static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND windowHandle;
    HDC memoryDC;
    texture* frameTexture;
};