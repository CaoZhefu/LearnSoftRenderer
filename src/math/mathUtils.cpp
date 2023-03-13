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
    finalColor.r = (unsigned char)(color01.r * 254.99f);
    finalColor.g = (unsigned char)(color01.g * 254.99f);
    finalColor.b = (unsigned char)(color01.b * 254.99f);
    finalColor.a = (unsigned char)(color01.a * 254.99f);
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

mat4 getViewMatrix(vec3 eye, vec3 center, vec3 up) {
    vec3 Zaxis = normalized(center - eye);
    vec3 Xaxis = normalized(cross(Zaxis, up));
    vec3 Yaxis = cross(Xaxis, Zaxis);

    // 这里观察空间采用右手系，z轴朝向屏幕外，-z轴朝向屏幕内
    mat4 ret = getIdentityMatrix();
    ret[0][0] = Xaxis.x;
    ret[0][1] = Xaxis.y;
    ret[0][2] = Xaxis.z;
    ret[1][0] = Yaxis.x;
    ret[1][1] = Yaxis.y;
    ret[1][2] = Yaxis.z;
    ret[2][0] = -Zaxis.x;
    ret[2][1] = -Zaxis.y;
    ret[2][2] = -Zaxis.z;
    ret[0][3] = -(Xaxis * eye);
    ret[1][3] = -(Yaxis * eye);
    ret[2][3] = (Zaxis * eye);

    //std::cout << " View Matrix: " << std::endl << ret << std::endl;
    return ret;
}

mat4 getPerspectiveMatrix(float fov, float aspect, float znear, float zfar) {
    float tanHalfFov = tan(fov * 0.5f);

    mat4 ret;
    ret[0][0] = 1.0f / (aspect * tanHalfFov);
    ret[1][1] = 1.0f / tanHalfFov;
    ret[2][2] = - (zfar + znear) / (zfar - znear);
    ret[2][3] = - (2.0f * znear * zfar) / (zfar - znear);
    ret[3][2] = - 1.f;

    //std::cout << "Perspective Matrix: " << std::endl << ret << std::endl;
    return ret;
}