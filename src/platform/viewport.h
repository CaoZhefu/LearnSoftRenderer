#pragma once

#include <string>
#include <windows.h>

class viewport
{
public:
    unsigned int width, height;

    bool init(unsigned int _width, unsigned int _height, const char* _title);

    bool shouldClose();

    void destroy();

private:
    static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND windowHandle;
    HDC memoryDC;

    //static HWND createWindow(unsigned int _width, unsigned int _height, const char* _title);
};