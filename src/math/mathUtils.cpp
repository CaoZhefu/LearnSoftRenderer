#include "mathUtils.h"

float frac(float t) {
    float r = t - (int)t;
    if(r < 0.f)
        r = 1.0f - std::abs(r);

    return r;
}

vec3 normalized(const vec3& v) {
    vec3 ret(v.x, v.y, v.z);
    ret.normalize();
    return ret;
}

vec3 barycentric(vec2& A, vec2& B, vec2& C, vec2& p) {
    vec3 xvec(C.x - A.x, B.x - A.x, A.x - p.x);
    vec3 yvec(C.y - A.y, B.y - A.y, A.y - p.y);
    vec3 u = cross(xvec, yvec);
    if(std::abs(u.z) < 0.999f)
        return vec3(-1, 1, 1); // will thrown away by rasterizator

    return vec3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

color4 colorFromVec01(const vec4& color01)
{
    color4 finalColor;
    finalColor.r = (unsigned char)(color01.r * 255);
    finalColor.g = (unsigned char)(color01.g * 255);
    finalColor.b = (unsigned char)(color01.b * 255);
    finalColor.a = (unsigned char)(color01.a * 255);
    return finalColor;
}

mat4 getIdentityMatrix() {
    mat4 ret;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            ret[i][j] = (i == j ? 1.0f : 0.0f);
    return ret;
}

mat4 getTranslateMatrix(float x, float y, float z) {
    mat4 ret = getIdentityMatrix();
    ret[0][3] = x;
    ret[1][3] = y;
    ret[2][3] = z;
    return ret;
}

mat4 getScaleMatrix(float x, float y, float z) {
    mat4 ret = getIdentityMatrix();
    ret[0][0] = x;
    ret[1][1] = y;
    ret[2][2] = z;
    return ret;
}

mat4 lookat(vec3 eye, vec3 center, vec3 up) {
    vec3 f = normalized(center - eye);
    vec3 s = normalized(cross(up, f));
    vec3 u = cross(f, s);

    mat4 ret = getIdentityMatrix();
    ret[0][0] = s.x;
    ret[1][0] = s.y;
    ret[2][0] = s.z;
    ret[0][1] = u.x;
    ret[1][1] = u.y;
    ret[2][1] = u.z;
    ret[0][2] = f.x;
    ret[1][2] = f.y;
    ret[2][2] = f.z;
    ret[3][0] = -(s * eye);
    ret[3][1] = -(u * eye);
    ret[3][2] = -(f * eye);
    return ret;
}

mat4 getPerspectiveMatrix(float fov, float aspect, float znear, float zfar) {
    float fax = 1.0f / (float)tan(fov * 0.5f);
    mat4 ret;
    ret[0][0] = fax / aspect;
    ret[1][1] = fax;
    ret[2][2] = zfar / (zfar - znear);
    ret[3][2] = -znear * zfar / (zfar - znear);
    ret[2][3] = 1.f;
    return ret;
}