#pragma once

#include<cassert>
#include<iostream>

template<int n>
class vec
{
public:
    vec() = default;
    float operator[](const int i) const { assert(i >= 0 && i < n); return data[i]; }
    float& operator[](const int i) { assert(i >= 0 && i < n); return data[i]; }
    float length() { return *this * *this; }
    float data[n] = {0};
};

template<int n> float operator*(const vec<n>& lhs, const vec<n>& rhs);
template<int n> vec<n> operator+(const vec<n>& lhs, const vec<n>& rhs);
template<int n> vec<n> operator-(const vec<n>& lhs, const vec<n>& rhs);
template<int n> vec<n> operator*(const vec<n>& lhs, const float rhs);
template<int n> vec<n> operator*(const float lhs, const vec<n>& rhs);
template<int n> vec<n> operator/(const vec<n>& lhs, const float rhs);
template<int n> std::ostream& operator<<(std::ostream& out, const vec<n>& v);

template<> class vec<3>
{
public:
    vec() = default;
    vec(float x, float y, float z) : x(x), y(y), z(z) {}
    float operator[](const int i) const { assert(i >= 0 && i < 3); return i == 0 ? x : (i == 1 ? y : z); }
    float& operator[](const int i) { assert(i >= 0 && i < 3); return i == 0 ? x : (i == 1 ? y : z); }
    float length() { return *this * *this; }
    float x, y, z;
};

typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

template<int nRow, int nCol>
class mat
{
    vec<nCol> rows[nRow] = {{}};

    vec<nCol>& operator[](const int i) { assert(i >= 0 && i < nRow); return rows[i]; }
    const vec<nCol>& operator[](const int i) const { assert(i >= 0 && i < nRow); return rows[i]; }

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

template<int nRow, int nCol> vec<nCol> operator*(const vec<nRow>& lhs, const mat<nRow, nCol>& rhs);
template<int R1, int C1, int C2> mat<R1, C2> operator*(const mat<R1, C1>& lhs, const mat<C1, C2>& rhs);
template<int nRow, int nCol> mat<nRow, nCol> operator+(const mat<nRow, nCol>& lhs, const mat<nRow, nCol>& rhs);
template<int nRow, int nCol> mat<nRow, nCol> operator-(const mat<nRow, nCol>& lhs, const mat<nRow, nCol>& rhs);

typedef mat<4, 4> mat4;