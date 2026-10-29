#pragma once

typedef struct {
    float *zbuf;
    int    w, h;
} DepthBuffer;

DepthBuffer depth_create(int w, int h);
void        depth_clear(DepthBuffer *d);
void        depth_free(DepthBuffer *d);
