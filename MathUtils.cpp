#include "MathUtils.h"

float frac(float t)
{
    float r = t - (int)t;
    if(r < 0.f)
        r = 1.0f - std::abs(r);

    return r;
}

vec3 cross(const vec3& v1, const vec3& v2)
{
    return vec3{ v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

vec3 barycentric(vec2& A, vec2& B, vec2& C, vec2& p)
{
    vec3 xvec(C.x - A.x, B.x - A.x, A.x - p.x);
    vec3 yvec(C.y - A.y, B.y - A.y, A.y - p.y);
    vec3 u = cross(xvec, yvec);
    if(std::abs(u.z) < 0.999f)
        return vec3(-1, 1, 1); // will thrown away by rasterizator

    return vec3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}