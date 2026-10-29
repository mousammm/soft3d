#define SDL_GFX_IMPLEMENTATION
#include "../include/sh_gfx.h"
#include <stdbool.h>

uint32_t argb_to_u32(unsigned char a, unsigned char r, unsigned char g, unsigned char b) {
    return ((uint32_t)a << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

int main(int argc, char** argv) {

    sh_gfx* gfx = sh_gfx_init("soft rr", 800, 600);

    int quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) { if (event.type == SDL_QUIT) { quit = true; } }

        sh_gfx_clear(gfx, 0xFF000000);

        for (int j = 0; j < gfx->height; j++) {
            for (int i = 0; i < gfx->width; i++) {

                double u = (double)i / (gfx->width  - 1);
                double v = (double)j / (gfx->height - 1);

                unsigned char r = (unsigned char)(255 * (1.0 - v));
                unsigned char g = (unsigned char)(255 * (1.0 - u));
                unsigned char b = (unsigned char)(255 * (1.0 - v * u));

                sh_gfx_put_pixel(gfx, i, j, argb_to_u32(255, r, g, b));
            }
        }

        sh_gfx_render(gfx);
    }

    sh_gfx_cleanup(gfx);
    return 0;
}
