#pragma once
#include "vec.h"
#include "depthbuf.h"
#include "sh_gfx.h"

typedef struct {
    float x, y;
    float z;
    Vec3  wpos;
    Vec3  wnorm;
} SVert;

void raster_tri(sh_gfx *gfx, DepthBuffer *db,
                SVert v0, SVert v1, SVert v2,
                Vec3 light_dir);
