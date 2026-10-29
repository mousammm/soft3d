#define SDL_GFX_IMPLEMENTATION
#include "../include/sh_gfx.h"

int main(int argc, char** argv) {

    sh_gfx* gfx = sh_gfx_init("software renderer", 800, 600);

    int isRunning = 1;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) { if (event.type == SDL_QUIT) { isRunning = 0; } }

        sh_gfx_clear(gfx, 0xFF000000); // 0xAARRGGBB

        for (int j = 0; j < gfx->height; j++) {
            for (int i = 0; i < gfx->width; i++) {
                sh_gfx_put_pixel(gfx, i, j, 0xFFFF0000);
            }
        }

        sh_gfx_render(gfx);
    }

    sh_gfx_cleanup(gfx);
    return 0;
}
