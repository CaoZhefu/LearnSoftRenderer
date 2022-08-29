#pragma once

#include<cassert>
#include<iostream>

float frac(float t);

template<int n>
class vec
{
public:
    vec() = default;
    float operator[](const int i) const { assert(i >= 0 && i < n); return data[i]; }
    float& operator[](const int i) { assert(i >= 0 && i < n); return data[i]; }
    float length() { std::sqrt(*this * *this); }
    void normalize() { 
        float len = length();
        if(len > 0.f){
            for(int i = 0; i < n; ++i)
                data[i] /= len;
        }
    }

    float data[n] = {0};
};

template<int n> float operator*(const vec<n>& lhs, const vec<n>& rhs)
{
    float ret = 0.0f;
    for(int i = 0; i < n; ++i) ret += lhs[i] * rhs[i];
    return ret;
}

template<int n> vec<n> operator+(const vec<n>& lhs, const vec<n>& rhs)
{
    vec<n> ret = lhs;
    for(int i = 0; i < n; ++i) ret[i] += rhs[i];
    return ret;
}

template<int n> vec<n> operator-(const vec<n>& lhs, const vec<n>& rhs)
{
    vec<n> ret = lhs;
    for(int i = 0; i < n; ++i) ret[i] -= rhs[i];
    return ret;
}

template<int n> vec<n> operator*(const vec<n>& lhs, const float rhs)
{
    vec<n> ret = lhs;
    for(int i = 0; i < n; ++i) ret[i] *= rhs;
    return ret;
}

template<int n> vec<n> operator*(const float lhs, const vec<n>& rhs)
{
    vec<n> ret = rhs;
    for(int i = 0; i < n; ++i) ret[i] *= lhs;
    return ret;
}

template<int n> vec<n> operator/(const vec<n>& lhs, const float rhs)
{
    vec<n> ret = lhs;
    for(int i = 0; i < n; ++i) ret[i] /= rhs;
    return ret;
}

template<int n> std::ostream& operator<<(std::ostream& out, const vec<n>& v)
{
    for(int i = 0; i < n; ++i) out << v[i] << " ";
    return out;
}

template<> class vec<2>
{
public:
    vec() = default;
    vec(float x, float y) : x(x), y(y) {}
    float operator[](const int i) const { assert(i >= 0 && i < 2); return i == 0 ? x : y; }
    float& operator[](const int i) { assert(i >= 0 && i < 2); return i == 0 ? x : y; }
    float length() { return std::sqrt(*this * *this); }
    void normalize() { 
        float len = length();
        if(len > 0.f){
            x /= len;
            y /= len;
        }
    }

    float x, y;
};

template<> class vec<3>
{
public:
    vec() = default;
    vec(float x, float y, float z) : x(x), y(y), z(z) {}
    float operator[](const int i) const { assert(i >= 0 && i < 3); return i == 0 ? x : (i == 1 ? y : z); }
    float& operator[](const int i) { assert(i >= 0 && i < 3); return i == 0 ? x : (i == 1 ? y : z); }
    float length() { return std::sqrt(*this * *this); }
        void normalize() { 
        float len = length();
        if(len > 0.f){
            x /= len;
            y /= len;
            z /= len;
        }
    }

    float x, y, z;
};

typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

vec3 cross(const vec3& v1, const vec3& v2);

template<int nRow, int nCol>
class mat
{
public:
    vec<nCol> rows[nRow] = {{}};
    vec<nCol>& operator[](const int i) { assert(i >= 0 && i < nRow); return rows[i]; }
    const vec<nCol>& operator[](const int i) const { assert(i >= 0 && i < nRow); return rows[i]; }

    vec<nRow> col(int col_idx) const
    {
        vec<nRow> ret;
        for(int i = 0; i < nRow; ++i){
            ret[i] = rows[i][col_idx];
        }
        return ret;
    }

    static mat<nRow, nCol> get_identity()
    {
        mat<nRow, nCol> ret;
        for(int i = 0; i < nRow; ++i){
            for(int j = 0; j < nCol; ++j){
                ret[i][j] = (i == j ? 1.0f : 0.0f);
            }
        }
        return ret;
    }
};

template<int nRow, int nCol> vec<nRow> operator*(const mat<nRow, nCol>& lhs, const vec<nCol>& rhs)
{
    vec<nRow> ret;
    for(int i = 0; i < nRow; ++i)
        for(int j = 0; j < nCol; ++j)
            ret[i] += rhs[j] * lhs[i][j];
    return ret;
}

template<int R1, int C1, int C2> mat<R1, C2> operator*(const mat<R1, C1>& lhs, const mat<C1, C2>& rhs)
{
    mat<R1, C2> ret;
    for(int i = 0; i < R1; ++i)
        for(int j = 0; j < C2; ++j)
            ret[i][j] = lhs[i] * rhs.col(j);
    return ret;
}

template<int nRow, int nCol> mat<nRow, nCol> operator+(const mat<nRow, nCol>& lhs, const mat<nRow, nCol>& rhs)
{
    mat<nRow, nCol> ret = lhs;
    for(int i = 0; i < nRow; ++i)
        for(int j = 0; j < nCol; ++j)
            ret[i][j] += rhs[i][j];
    return ret;
}

template<int nRow, int nCol> mat<nRow, nCol> operator-(const mat<nRow, nCol>& lhs, const mat<nRow, nCol>& rhs)
{
    mat<nRow, nCol> ret = lhs;
    for(int i = 0; i < nRow; ++i)
        for(int j = 0; j < nCol; ++j)
            ret[i][j] -= rhs[i][j];
    return ret;
}

typedef mat<4, 4> mat4;

template<int nRow, int nCol> std::ostream& operator<<(std::ostream& out, const mat<nRow, nCol>& m)
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