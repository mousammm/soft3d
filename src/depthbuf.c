#include "../include/depthbuf.h"
#include <stdlib.h>
#include <math.h>

DepthBuffer depth_create(int w, int h){
    DepthBuffer d = {0};
    d.w = w; d.h = h;
    d.zbuf = malloc(sizeof(float) * w * h);
    return d;
}
void depth_clear(DepthBuffer *d){
    int n = d->w * d->h;
    for (int i = 0; i < n; i++) d->zbuf[i] = INFINITY;
}
void depth_free(DepthBuffer *d){ free(d->zbuf); d->zbuf = NULL; }
