#include "../include/vec.h"

Vec3 v3(float x, float y, float z)
{
    return (Vec3){x, y, z};
}

Vec3 v3_add(Vec3 a, Vec3 b)
{
    return v3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 v3_sub(Vec3 a, Vec3 b)
{
    return v3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 v3_scale(Vec3 a, float s)
{
    return v3(a.x * s, a.y * s, a.z * s);
}

float v3_dot(Vec3 a, Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 v3_cross(Vec3 a, Vec3 b)
{
    return v3(a.y * b.z - a.z * b.y,
              a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

float v3_len(Vec3 a)
{
    return sqrtf(v3_dot(a, a));
}

Vec3 v3_norm(Vec3 a)
{
    float l = v3_len(a);
    return l > 1e-8f ? v3_scale(a, 1.0f / l) : v3(0, 0, 0);
}
