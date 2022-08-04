#include "MathUtils.h"

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

// template<int n> std::ostream& operator<<(std::ostream& out, const vec<n>& v)
// {
//     for(int i = 0; i < n; ++i) out << v[i] << " ";
//     return out;
// }

// template<int nRow, int nCol> vec<nCol> operator*(const vec<nRow>& lhs, const mat<nRow, nCol>& rhs)
// {
//     vec<nCol> ret;
//     for(int i = 0; i < nCol; ++i){
//         for(int j = 0; j < nRow; ++j){
//             ret[i] += lhs[j] * rhs[j][i];
//         }
//     }
//     return ret;
// }

template<int R1, int C1, int C2> mat<R1, C2> operator*(const mat<R1, C1>& lhs, const mat<C1, C2>& rhs)
{

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