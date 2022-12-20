#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "renderer.h"
#include "root_directory.h"
#include "SDL.h"

int main(int argc, char * argv[])
{
    bool quit = false;
    bool leftMouseButtonDown = false;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window * window = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
    Uint32* pixels = new Uint32[640 * 480];
    memset(pixels, 255, 640 * 480 * sizeof(Uint32));
 
    while (!quit)
    {
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));

        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = true;
                break;
            case SDL_MOUSEMOTION:
                if(leftMouseButtonDown)
                {
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    pixels[mouseY * 640 + mouseX] = 0;
                } 
                break;
        }
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
 
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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