#ifndef VEC_H
#define VEC_H

#include <math.h>

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    float x, y, z, w;
} Vec4;

#define VECDEF static inline
#if !defined (VECDEF)
Vec3  v3(float x, float y, float z);
Vec3  v3_add(Vec3 a, Vec3 b);
Vec3  v3_sub(Vec3 a, Vec3 b);
Vec3  v3_scale(Vec3 a, float s);
float v3_dot(Vec3 a, Vec3 b);
Vec3  v3_cross(Vec3 a, Vec3 b);
float v3_len(Vec3 a);
Vec3  v3_norm(Vec3 a);
#endif

VECDEF Vec3 v3(float x, float y, float z)
{
    return (Vec3){x, y, z};
}

VECDEF Vec3 v3_add(Vec3 a, Vec3 b)
{
    return v3(a.x + b.x,
              a.y + b.y,
              a.z + b.z);
}

VECDEF Vec3 v3_sub(Vec3 a, Vec3 b)
{ 
    return v3(a.x - b.x,
              a.y - b.y,
              a.z - b.z);
}

VECDEF Vec3 v3_scale(Vec3 a, float s)
{
    return v3(a.x * s,
              a.y * s, 
              a.z * s);
}

VECDEF float v3_dot(Vec3 a, Vec3 b)
{ 
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

VECDEF Vec3 v3_cross(Vec3 a, Vec3 b)
{
    return v3(a.y * b.z - a.z * b.y,
              a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

VECDEF float v3_len(Vec3 a)
{
    return sqrtf(v3_dot(a, a));
}

VECDEF Vec3 v3_norm(Vec3 a)
{
    float l = v3_len(a);
    return l > 1e-8f ? v3_scale(a, 1.0f / l) : v3(0, 0, 0);
}

#endif
