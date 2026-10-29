#include "../include/mat.h"
#include <math.h>

Mat4 mat4_identity(void){
    Mat4 r = {0};
    r.m[0][0] = r.m[1][1] = r.m[2][2] = r.m[3][3] = 1.0f;
    return r;
}

Mat4 mat4_mul(Mat4 a, Mat4 b){
    Mat4 r = {0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                r.m[i][j] += a.m[i][k] * b.m[k][j];
    return r;
}

Vec4 mat4_mul_vec4(Mat4 m, Vec4 v){
    return (Vec4){
        m.m[0][0]*v.x + m.m[0][1]*v.y + m.m[0][2]*v.z + m.m[0][3]*v.w,
        m.m[1][0]*v.x + m.m[1][1]*v.y + m.m[1][2]*v.z + m.m[1][3]*v.w,
        m.m[2][0]*v.x + m.m[2][1]*v.y + m.m[2][2]*v.z + m.m[2][3]*v.w,
        m.m[3][0]*v.x + m.m[3][1]*v.y + m.m[3][2]*v.z + m.m[3][3]*v.w,
    };
}

Mat4 mat4_rot_y(float r){
    Mat4 m = mat4_identity();
    float c = cosf(r), s = sinf(r);
    m.m[0][0] =  c; m.m[0][2] = s;
    m.m[2][0] = -s; m.m[2][2] = c;
    return m;
}

Mat4 mat4_scale(Vec3 s){
    Mat4 m = mat4_identity();
    m.m[0][0] = s.x; m.m[1][1] = s.y; m.m[2][2] = s.z;
    return m;
}

Mat4 mat4_perspective(float fovy, float aspect, float n, float f){
    float t = 1.0f / tanf(fovy * 0.5f);
    Mat4 r = {0};
    r.m[0][0] = t / aspect;
    r.m[1][1] = t;
    r.m[2][2] = (f + n) / (n - f);
    r.m[2][3] = (2.0f * f * n) / (n - f);
    r.m[3][2] = -1.0f;
    return r;
}

Mat4 mat4_look_at(Vec3 eye, Vec3 target, Vec3 up){
    Vec3 f = v3_norm(v3_sub(target, eye));
    Vec3 s = v3_norm(v3_cross(f, up));
    Vec3 u = v3_cross(s, f);
    Mat4 r = mat4_identity();
    r.m[0][0]=s.x; r.m[0][1]=s.y; r.m[0][2]=s.z; r.m[0][3]=-v3_dot(s,eye);
    r.m[1][0]=u.x; r.m[1][1]=u.y; r.m[1][2]=u.z; r.m[1][3]=-v3_dot(u,eye);
    r.m[2][0]=-f.x;r.m[2][1]=-f.y;r.m[2][2]=-f.z;r.m[2][3]= v3_dot(f,eye);
    return r;
}
