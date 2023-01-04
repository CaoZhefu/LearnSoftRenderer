#include "viewport.h"

static const char* const WINDOW_CLASS_NAME = "WindowClass";
static const char* const WINDOW_ENTRY_NAME = "WindowEntry";

bool viewport::init(unsigned int _width, unsigned int _height, const char* _title)
{
    // 1. Register Class
    WNDCLASS windowClass;
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = windowProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = WINDOW_CLASS_NAME;

    if(!RegisterClass(&windowClass))
    {
        MessageBox(0, "Register Class Failed", 0, 0);
        return false;
    }

    // 2. Create Window
    DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    RECT rect; rect.left = 0; rect.top = 0; rect.right = _width; rect.bottom = _height;
    AdjustWindowRect(&rect, style, 0);
    _width = rect.right - rect.left; _height = rect.bottom - rect.top;
    windowHandle = CreateWindow(WINDOW_CLASS_NAME, _title, style, CW_USEDEFAULT, CW_USEDEFAULT, 
                                _width, _height, NULL, NULL, GetModuleHandle(NULL), NULL);
    if(windowHandle == NULL)
    {
        MessageBox(0, "Create Window Failed", 0, 0);
        return false;
    }

    ShowWindow(windowHandle, SW_SHOW);
    return true;
}

LRESULT viewport::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool viewport::shouldClose()
{
    return false;
}

void viewport::destroy()
{
    ShowWindow(windowHandle, SW_HIDE);
    DeleteDC(memoryDC);
    DestroyWindow(windowHandle);
}