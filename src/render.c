#include "../include/render.h"
#include "../include/raster.h"
#include "../include/mat.h"
#include "../include/vec.h"
#include "../include/mesh.h"
#include "../include/depthbuf.h"
#include "../include/sh_gfx.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void render_mesh(sh_gfx *gfx, DepthBuffer *db, const Mesh *mesh,
                 Mat4 mvp, Mat4 model, Vec3 light_dir)
{
    for (int i = 0; i < mesh->nindices; i += 3){
        SVert sv[3];
        bool ok = true;

        for (int c = 0; c < 3; c++){
            const Vertex *vx = &mesh->verts[mesh->indices[i + c]];

            Vec4 clip = mat4_mul_vec4(mvp, (Vec4){vx->pos.x, vx->pos.y, vx->pos.z, 1.0f});
            if (clip.w <= 1e-4f){ ok = false; break; }

            float ndcx = clip.x / clip.w;
            float ndcy = clip.y / clip.w;
            float ndcz = clip.z / clip.w;

            sv[c].x = (ndcx * 0.5f + 0.5f) * (float)gfx->width;
            sv[c].y = (1.0f - (ndcy * 0.5f + 0.5f)) * (float)gfx->height;
            sv[c].z = ndcz;

            Vec4 wp = mat4_mul_vec4(model, (Vec4){vx->pos.x, vx->pos.y, vx->pos.z, 1.0f});
            sv[c].wpos = v3(wp.x, wp.y, wp.z);

            Vec4 wn = mat4_mul_vec4(model, (Vec4){vx->normal.x, vx->normal.y, vx->normal.z, 0.0f});
            sv[c].wnorm = v3_norm(v3(wn.x, wn.y, wn.z));
        }
        if (!ok) continue;

        raster_tri(gfx, db, sv[0], sv[1], sv[2], light_dir);
    }
}
