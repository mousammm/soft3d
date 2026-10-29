#include "../include/sh_gfx.h"
#include "../include/mat.h"
#include "../include/vec.h"
#include "../include/mesh.h"
#include "../include/depthbuf.h"
#include "../include/render.h"

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(int argc, char** argv){
    if (argc < 2){
        fprintf(stderr, "Usage: %s model.obj\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    Mesh mesh = load_obj(path);
    if (mesh.nverts == 0){
        fprintf(stderr, "Empty mesh from %s\n", path);
        return 1;
    }
    printf("Loaded %s: %d verts, %d indices (%d tris)\n",
           path, mesh.nverts, mesh.nindices, mesh.nindices / 3);

    sh_gfx *gfx = sh_gfx_init("software renderer", 800, 600);
    DepthBuffer db = depth_create(gfx->width, gfx->height);

    float yaw = 0.5f, pitch = 0.4f, dist = 3.0f;
    bool dragging = false;
    int lastx = 0, lasty = 0;

    bool quit = false;
    SDL_Event event;
    Uint64 start = SDL_GetTicks64();

    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) quit = true;
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                dragging = true; lastx = event.button.x; lasty = event.button.y;
            }
            else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT){
                dragging = false;
            }
            else if (event.type == SDL_MOUSEMOTION && dragging){
                int dx = event.motion.x - lastx;
                int dy = event.motion.y - lasty;
                lastx = event.motion.x;
                lasty = event.motion.y;
                yaw   -= dx * 0.01f;
                pitch += dy * 0.01f;
                if (pitch >  1.4f) pitch =  1.4f;
                if (pitch < -1.4f) pitch = -1.4f;
            }
            else if (event.type == SDL_MOUSEWHEEL){
                dist -= event.wheel.y * 0.2f;
                if (dist < 0.5f) dist = 0.5f;
                if (dist > 50.0f) dist = 50.0f;
            }
        }

        float t = (float)(SDL_GetTicks64() - start) / 1000.0f;

        Vec3 eye = v3(
            dist * cosf(pitch) * sinf(yaw),
            dist * sinf(pitch),
            dist * cosf(pitch) * cosf(yaw)
        );
        Mat4 view = mat4_look_at(eye, v3(0,0,0), v3(0,1,0));
        Mat4 proj = mat4_perspective(60.0f * (float)M_PI / 180.0f,
                                     (float)gfx->width / (float)gfx->height,
                                     0.05f, 100.0f);

        Mat4 model = mat4_rot_y(t * 0.5f);
        Mat4 mvp = mat4_mul(mat4_mul(proj, view), model);
        Vec3 light_dir = v3_norm(v3(0.5f, 0.7f, 0.6f));

        sh_gfx_clear(gfx, 0xFF101018);
        depth_clear(&db);
        render_mesh(gfx, &db, &mesh, mvp, model, light_dir);
        sh_gfx_render(gfx);
    }

    depth_free(&db);
    mesh_free(&mesh);
    sh_gfx_cleanup(gfx);
    return 0;
}
