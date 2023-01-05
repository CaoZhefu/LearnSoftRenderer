#include "viewport.h"
#include <assert.h>

static const char* const WINDOW_CLASS_NAME = "WindowClass";
static const char* const WINDOW_ENTRY_NAME = "WindowEntry";

viewport::viewport()
{
    shouldClose = false;
    width = 0;
    height = 0;
    frameTexture = nullptr;
}

bool viewport::init(int _width, int _height, const char* _title)
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
    this->width = _width;
    this->height = _height;
    windowHandle = CreateWindow(WINDOW_CLASS_NAME, _title, style, CW_USEDEFAULT, CW_USEDEFAULT, 
                                _width, _height, NULL, NULL, GetModuleHandle(NULL), NULL);
    if(windowHandle == NULL)
    {
        MessageBox(0, "Create Window Failed", 0, 0);
        return false;
    }

    // 3. Create frame Buffer
    frameTexture = new texture(_width, _height, 4);
    frameTexture->clearData();
    BITMAPINFOHEADER bitmapInfoHeader;
    HBITMAP dib_bitmap;
    HBITMAP old_bitmap;
    HDC windowDC;

    windowDC = GetDC(windowHandle);
    memoryDC = CreateCompatibleDC(windowDC);
    ReleaseDC(windowHandle, windowDC);

    memset(&bitmapInfoHeader, 0, sizeof(BITMAPINFOHEADER));
    bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfoHeader.biWidth = _width;
    bitmapInfoHeader.biHeight = -_height;
    bitmapInfoHeader.biPlanes = 1;
    bitmapInfoHeader.biBitCount = 32;
    bitmapInfoHeader.biCompression = BI_RGB;
    dib_bitmap = CreateDIBSection(memoryDC, (BITMAPINFO*)&bitmapInfoHeader, DIB_RGB_COLORS, (void**)&frameTexture->data, NULL, 0);
    if(dib_bitmap == NULL)
    {
        MessageBox(0, "Create DIB Bitmap Failed", 0, 0);
        return false;
    }
    old_bitmap = (HBITMAP)SelectObject(memoryDC, dib_bitmap);
    DeleteObject(old_bitmap);

    SetProp(windowHandle, WINDOW_ENTRY_NAME, this);
    ShowWindow(windowHandle, SW_SHOW);
    return true;
}

LRESULT viewport::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(viewport* v = (viewport*)GetProp(hWnd, WINDOW_ENTRY_NAME))
    {
        if(uMsg == WM_CLOSE)
        {
            v->shouldClose = true;
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void viewport::destroy()
{
    ShowWindow(windowHandle, SW_HIDE);
    RemoveProp(windowHandle, WINDOW_ENTRY_NAME);
    DeleteDC(memoryDC);
    DestroyWindow(windowHandle);
    delete frameTexture;
}

void viewport::renderCopy(renderer* r)
{
    assert(width == r->width && height == r->height);

    for(int row = 0; row < height; ++row)
    {
        for(int col = 0; col < width; ++col)
        {
            int bufferIndex = (row * width + col) * 3;
            int frameIndex = (row * width + col) * 4;
            unsigned char* bufferPixel = &r->frameBuffer[bufferIndex];
            unsigned char* framePixel = &frameTexture->data[frameIndex];
            framePixel[0] = bufferPixel[2]; // B
            framePixel[1] = bufferPixel[1]; // G
            framePixel[2] = bufferPixel[0]; // R
        }
    }
}

void viewport::updateBuffers()
{
    HDC windowDC = GetDC(windowHandle);
    BitBlt(windowDC, 0, 0, width, height, memoryDC, 0, 0, SRCCOPY);
    ReleaseDC(windowHandle, windowDC);
}

void viewport::pollEvents()
{
    MSG message;
    while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}