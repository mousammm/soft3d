#pragma once
#include <stdint.h>
#include "vec.h"

typedef struct {
    Vec3 pos;
    Vec3 normal;
} Vertex;

typedef struct {
    Vertex   *verts;
    uint32_t *indices;
    int       nverts;
    int       nindices;
} Mesh;

Mesh load_obj(const char *path);
void mesh_free(Mesh *m);
