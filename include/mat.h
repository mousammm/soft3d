#ifndef MATRIX_H
#define MATRIX_H

#include "./vec.h"

typedef struct {
    float m[4][4];
} Mat4;

Mat4 mat4_identity(void);
Mat4 mat4_mul_mat4(Mat4 a, Mat4 b);
Vec4 mat4_mul_vec4(Mat4 m, Vec4 v);
Mat4 mat4_rot_y(float r);
Mat4 mat4_scale(Vec3 s);
Mat4 mat4_perspective(float fovy, float aspect, float n, float f);
Mat4 mat4_look_at(Vec3 eye, Vec3 target, Vec3 up);

#endif // MATRIX_H
