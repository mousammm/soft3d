#pragma once
typedef struct { float x, y, z; } Vec3;
typedef struct { float x, y, z, w; } Vec4;

Vec3  v3(float x, float y, float z);
Vec3  v3_add(Vec3 a, Vec3 b);
Vec3  v3_sub(Vec3 a, Vec3 b);
Vec3  v3_scale(Vec3 a, float s);
float v3_dot(Vec3 a, Vec3 b);
Vec3  v3_cross(Vec3 a, Vec3 b);
float v3_len(Vec3 a);
Vec3  v3_norm(Vec3 a);
