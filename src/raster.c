#include "../include/raster.h"
#include <math.h>
#include <stdint.h>

static float edge_func(float ax, float ay, float bx, float by, float px, float py){
    return (px - ax) * (by - ay) - (py - ay) * (bx - ax);
}

void raster_tri(sh_gfx *gfx, DepthBuffer *db,
                SVert v0, SVert v1, SVert v2,
                Vec3 light_dir)
{
    int minX = (int)floorf(fminf(v0.x, fminf(v1.x, v2.x)));
    int maxX = (int)ceilf (fmaxf(v0.x, fmaxf(v1.x, v2.x)));
    int minY = (int)floorf(fminf(v0.y, fminf(v1.y, v2.y)));
    int maxY = (int)ceilf (fmaxf(v0.y, fmaxf(v1.y, v2.y)));
    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;
    if (maxX >= gfx->width)  maxX = gfx->width  - 1;
    if (maxY >= gfx->height) maxY = gfx->height - 1;
    if (minX > maxX || minY > maxY) return;

    float area = edge_func(v0.x, v0.y, v1.x, v1.y, v2.x, v2.y);
    if (fabsf(area) < 1e-6f) return;

    float inv_area = 1.0f / area;

    for (int y = minY; y <= maxY; y++){
        for (int x = minX; x <= maxX; x++){
            float px = (float)x + 0.5f;
            float py = (float)y + 0.5f;

            float w0 = edge_func(v1.x, v1.y, v2.x, v2.y, px, py) * inv_area;
            float w1 = edge_func(v2.x, v2.y, v0.x, v0.y, px, py) * inv_area;
            float w2 = 1.0f - w0 - w1;

            if (w0 < 0 || w1 < 0 || w2 < 0){
                if (w0 > 0 || w1 > 0 || w2 > 0) continue;
            }

            float z = w0*v0.z + w1*v1.z + w2*v2.z;
            int idx = y * gfx->width + x;
            if (z < db->zbuf[idx]){
                db->zbuf[idx] = z;

                Vec3 n = v3_add(v3_add(v3_scale(v0.wnorm, w0),
                                       v3_scale(v1.wnorm, w1)),
                                       v3_scale(v2.wnorm, w2));
                n = v3_norm(n);

                float ndl = v3_dot(n, light_dir);
                if (ndl < 0) ndl = 0;
                float ambient = 0.15f;
                float lum = ambient + 0.85f * ndl;
                if (lum > 1) lum = 1;
                unsigned char c = (unsigned char)(lum * 255.0f);

                uint32_t px32 = ((uint32_t)255 << 24) | ((uint32_t)c << 16)
                                                     | ((uint32_t)c << 8)
                                                     |  (uint32_t)c;
                sh_gfx_put_pixel(gfx, x, y, px32);
            }
        }
    }
}
