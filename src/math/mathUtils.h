#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <memory>

float frac(float t);

template<typename T>
T clamp(T x, T min, T max) {
    return x < min ? min : (x > max ? max : x);
}

template<int n, class T>
class vec
{
public:
    vec() { for(int i = 0; i < n; ++i) data[i] = 0.f; }
    T operator[](const int i) const { assert(i >= 0 && i < n); return data[i]; }
    T& operator[](const int i) { assert(i >= 0 && i < n); return data[i]; }
    float length() { std::sqrt(*this * *this); }
    void normalize() { 
        float len = length();
        if(len > 0.f){
            for(int i = 0; i < n; ++i)
                data[i] /= len;
        }
    }

    T data[n];
};

template<int n, class T> float operator*(const vec<n, T>& lhs, const vec<n, T>& rhs)
{
    float ret = 0.0f;
    for(int i = 0; i < n; ++i) ret += lhs[i] * rhs[i];
    return ret;
}

template<int n, class T> vec<n, T> operator+(const vec<n, T>& lhs, const vec<n, T>& rhs)
{
    vec<n, T> ret = lhs;
    for(int i = 0; i < n; ++i) ret[i] += rhs[i];
    return ret;
}

template<int n, class T> vec<n, T> operator-(const vec<n, T>& lhs, const vec<n, T>& rhs)
{
    vec<n, T> ret = lhs;
    for(int i = 0; i < n; ++i) ret[i] -= rhs[i];
    return ret;
}

template<int n, class T> vec<n, T> operator-(const vec<n, T>& lhs, const T rhs)
{
    vec<n, T> ret = lhs;
    for(int i = 0; i < n; ++i) ret[i] -= rhs;
    return ret;
}

template<int n, class T> vec<n, T> operator*(const vec<n, T>& lhs, const float rhs)
{
    vec<n, T> ret = lhs;
    for(int i = 0; i < n; ++i) ret[i] *= rhs;
    return ret;
}

template<int n, class T> vec<n, T> operator*(const float lhs, const vec<n, T>& rhs)
{
    vec<n, T> ret = rhs;
    for(int i = 0; i < n; ++i) ret[i] *= lhs;
    return ret;
}

template<int n, class T> vec<n, T> operator/(const vec<n, T>& lhs, const float rhs)
{
    vec<n, T> ret = lhs;
    for(int i = 0; i < n; ++i) ret[i] /= rhs;
    return ret;
}

template<int n, class T> std::ostream& operator<<(std::ostream& out, const vec<n, T>& v)
{
    for(int i = 0; i < n; ++i) out << v[i] << " ";
    return out;
}

template<class T> class vec<2, T>
{
public:
    union 
    {
        struct { T x, y; };
        struct { T u, v; };
        T m[2];
    };

    vec() : x(0), y(0) {}
    vec(T x, T y) : x(x), y(y) {}
    T operator[](const int i) const { assert(i >= 0 && i < 2); return m[i]; }
    T& operator[](const int i) { assert(i >= 0 && i < 2); return m[i]; }
    float length() { return std::sqrt(*this * *this); }
    void normalize() { 
        float len = length();
        if(len > 0.f){
            x /= len;
            y /= len;
        }
    }
};
typedef vec<2, float> vec2;
typedef vec<2, int> vec2i;

template<class T> class vec<3, T>
{
public:
    union 
    {
        struct { T x, y, z; };
        struct { T r, g, b; };
        T m[3];
    };

    vec() : x(0), y(0), z(0) {}
    vec(T x, T y, T z) : x(x), y(y), z(z) {}
    T operator[](const int i) const { assert(i >= 0 && i < 3); return m[i]; }
    T& operator[](const int i) { assert(i >= 0 && i < 3); return m[i]; }
    float length() { return std::sqrt(*this * *this); }
    void normalize() { 
        float len = length();
        if(len > 0.f){
            x /= len;
            y /= len;
            z /= len;
        }
    }
};
typedef vec<3, float> vec3;
typedef vec<3, int> vec3i;

template<class T> class vec<4, T>
{
public:
    union 
    {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        T m[4];
    };

    vec() : x(0), y(0), z(0), w(0) {}
    vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    vec(vec<3, T>& v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}
    T operator[](const int i) const { 
        assert(i >= 0 && i < 4);
        return m[i];
    }
    T& operator[](const int i) { 
        assert(i >= 0 && i < 4);
        return m[i];
    }
    float length() { return std::sqrt(*this * *this); }
    void normalize() { 
        float len = length();
        if(len > 0.f){
            x /= len;
            y /= len;
            z /= len;
        }
    }

    vec<3, T> xyz() const
    {
        return vec<3, T>(x, y, z);
    }
};
typedef vec<4, float> vec4;
typedef vec<4, unsigned char> color4;

template<class T>
inline T cross(const vec<2, T>& v1, const vec<2, T>& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

template<class T>
inline vec<3, T> cross(const vec<3, T>& v1, const vec<3, T>& v2) {
    return vec<3, T>{ v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

vec3 normalized(const vec3& v);

template<int nRow, int nCol, class T>
class mat
{
public:
    vec<nCol, T> rows[nRow];
    vec<nCol, T>& operator[](const int i) { assert(i >= 0 && i < nRow); return rows[i]; }
    const vec<nCol, T>& operator[](const int i) const { assert(i >= 0 && i < nRow); return rows[i]; }

    vec<nRow, T> getCol(int col_idx) const {
        vec<nRow, T> ret;
        for(int i = 0; i < nRow; ++i){
            ret[i] = rows[i][col_idx];
        }
        return ret;
    }
};

typedef mat<4, 4, float> mat4;

inline mat4 getIdentityMatrix();
inline mat4 getTranslateMatrix(float x, float y, float z);
inline mat4 getScaleMatrix(float x, float y, float z);
//mat4 getRotateMatrix();
mat4 getViewMatrix(vec3 eye, vec3 center, vec3 up);
mat4 getPerspectiveMatrix(float fov, float aspect, float znear, float zfar);

template<int nRow, int nCol, class T> vec<nRow, T> operator*(const mat<nRow, nCol, T>& lhs, const vec<nCol, T>& rhs)
{
    vec<nRow, T> ret;
    for(int i = 0; i < nRow; ++i)
        for(int j = 0; j < nCol; ++j)
            ret[i] += rhs[j] * lhs[i][j];
    return ret;
}

template<int R1, int C1, int C2, class T> mat<R1, C2, T> operator*(const mat<R1, C1, T>& lhs, const mat<C1, C2, T>& rhs)
{
    mat<R1, C2, T> ret;
    for(int i = 0; i < R1; ++i)
        for(int j = 0; j < C2; ++j)
            ret[i][j] = lhs[i] * rhs.getCol(j);
    return ret;
}

template<int nRow, int nCol, class T> mat<nRow, nCol, T> operator+(const mat<nRow, nCol, T>& lhs, const mat<nRow, nCol, T>& rhs)
{
    mat<nRow, nCol, T> ret = lhs;
    for(int i = 0; i < nRow; ++i)
        for(int j = 0; j < nCol; ++j)
            ret[i][j] += rhs[i][j];
    return ret;
}

template<int nRow, int nCol, class T> mat<nRow, nCol, T> operator-(const mat<nRow, nCol, T>& lhs, const mat<nRow, nCol, T>& rhs)
{
    mat<nRow, nCol, T> ret = lhs;
    for(int i = 0; i < nRow; ++i)
        for(int j = 0; j < nCol; ++j)
            ret[i][j] -= rhs[i][j];
    return ret;
}

template<int nRow, int nCol, class T> std::ostream& operator<<(std::ostream& out, const mat<nRow, nCol, T>& m)
{
    for(int i = 0; i < nRow; ++i){
        for(int j = 0; j < nCol; ++j){
            out << m[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

// 求三角形ABC中p点重心坐标
vec3 barycentric(vec2& A, vec2& B, vec2& C, vec2& p);

// 将0-1的向量转换为颜色
inline static color4 colorFromVec01(vec4& color01)
{
    for(int i = 0; i < 4; ++i)
    {
        color01[i] = clamp(color01[i], 0.f, 1.f);
    }

    color4 finalColor;
    finalColor.r = (unsigned char)(color01.r * 255.f);
    finalColor.g = (unsigned char)(color01.g * 255.f);
    finalColor.b = (unsigned char)(color01.b * 255.f);
    finalColor.a = (unsigned char)(color01.a * 255.f);
    return finalColor;
}

// 将0-255的值转为0-1
inline static float color01From255(unsigned char color)
{
    return (float)color / 255.0f;
}

template<typename... Args>
std::string string_format(const std::string& format, Args&&... args) {
	size_t size = std::snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args)...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), std::forward<Args>(args)...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}