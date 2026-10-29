#pragma once
#include "mat.h"
#include "mesh.h"
#include "depthbuf.h"
#include "sh_gfx.h"

void render_mesh(sh_gfx *gfx, DepthBuffer *db, const Mesh *mesh,
                 Mat4 mvp, Mat4 model, Vec3 light_dir);
