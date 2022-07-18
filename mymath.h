#pragma once

#include <cmath>
#include <memory>

int clamp(int x, int max, int min) { return (x < min) ? min : ((x > max) ? max : x); }
float interp(float x1, float x2, float t) { return x1 + (x2 - x1) * t; }

struct mat4;

// 向量
struct vec4
{
    float x, y, z, w;

    float length() { return sqrt(x * x + y * y + z * z); } 

    vec4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f) : x(x), y(y), z(z), w(w) {}

    vec4 operator+ (vec4& v){
        return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    vec4 operator- (vec4& v){
        return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    void operator+= (vec4& v){
        x = x + v.x;
        y = y + v.y;
        z = z + v.z;
        w = w + v.w;
    }

    void operator-= (vec4& v){
        x = x - v.x;
        y = y - v.y;
        z = z - v.z;
        w = w - v.w;
    }

    vec4 operator* (mat4& m);
    void operator*= (mat4& m);

    void normalize(){
        float len = length();
        if(len != 0.f){
            float inv = 1.f / len;
            x *= inv;
            y *= inv;
            z *= inv;
        }
    }
};

// 矩阵
struct mat4
{
    float data[4][4];

    float* operator[] (const int i) { return data[i]; }

    void operator+= (mat4& m){
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                data[i][j] += m[i][j];
            }
        }
    }

    void operator-= (mat4& m){
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                data[i][j] -= m[i][j];
            }
        }
    }

    mat4 operator+ (mat4& m){
        mat4 res;
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                res[i][j] = (*this)[i][j] + m[i][j];
            }
        }
        return res;
    }

    mat4 operator- (mat4& m){
        mat4 res;
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                res[i][j] = (*this)[i][j] - m[i][j];
            }
        }
        return res;
    }

    mat4 operator* (mat4 &m){
        mat4 res;
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                res[i][j] = (*this)[i][0] * m[0][j] +
                            (*this)[i][1] * m[1][j] +
                            (*this)[i][2] * m[2][j] +
                            (*this)[i][3] * m[3][j];
            }
        }
        return res;
    }

    void set_zero(){
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                data[i][j] = 0.f;
            }
        }
    }

    void set_identity(){
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                if(i != j)
                    data[i][j] = 0.f;
                else
                    data[i][j] = 1.f;
            }
        }
    }
};

// 平移矩阵
mat4 get_translate_mat(float x, float y, float z){
    mat4 res;
    res.set_identity();
    res[0][3] = x;
    res[1][3] = y;
    res[2][3] = z;
    return res;
}

// 缩放矩阵
mat4 get_scale_mat(float x, float y, float z){
    mat4 res;
    res.set_identity();
    res[0][0] = x;
    res[1][1] = y;
    res[2][2] = z;
    return res;
}

// 旋转矩阵
mat4 get_rotate_mat(float x, float y, float z, float theta){
    mat4 res;
    float qsin = (float)sin(theta * 0.5f);
	float qcos = (float)cos(theta * 0.5f);
	vec4 vec = { x, y, z, 1.0f };
    vec.normalize();
	float w = qcos;
	x = vec.x * qsin;
	y = vec.y * qsin;
	z = vec.z * qsin;
	res[0][0] = 1 - 2 * y * y - 2 * z * z;
	res[1][0] = 2 * x * y - 2 * w * z;
	res[2][0] = 2 * x * z + 2 * w * y;
	res[0][1] = 2 * x * y + 2 * w * z;
	res[1][1] = 1 - 2 * x * x - 2 * z * z;
	res[2][1] = 2 * y * z - 2 * w * x;
	res[0][2] = 2 * x * z - 2 * w * y;
	res[1][2] = 2 * y * z + 2 * w * x;
	res[2][2] = 1 - 2 * x * x - 2 * y * y;
	res[0][3] = res[1][3] = res[2][3] = 0.0f;
	res[3][0] = res[3][1] = res[3][2] = 0.0f;	
	res[3][3] = 1.0f;
    return res;
}

vec4 vec_interp(vec4& v1, vec4& v2, float t){
    return vec4(interp(v1.x, v2.x, t), interp(v1.y, v2.y, t), interp(v1.z, v2.z, t), 1.f);
}

float vec_dot(vec4& v1, vec4& v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec4 vec_cross(vec4& v1, vec4& v2){
    float rx = v1.y * v2.z - v1.z * v2.y;
    float ry = v1.z * v2.x - v1.x * v2.z;
    float rz = v1.x * v2.y - v1.y * v2.x;
    return vec4(rx, ry, rz, 1.f);
}

void vec4::operator*=(mat4& m){
    float tx = x, ty = y, tz = z, tw = w;
    x = tx * m[0][0] + ty * m[1][0] + tz * m[2][0] + tw * m[3][0];
    y = tx * m[0][1] + ty * m[1][1] + tz * m[2][1] + tw * m[3][1];
    z = tx * m[0][2] + ty * m[1][2] + tz * m[2][2] + tw * m[3][2];
    w = tx * m[0][3] + ty * m[1][3] + tz * m[2][3] + tw * m[3][3];
}

vec4 vec4::operator*(mat4& m){
    vec4 res;
    float tx = x, ty = y, tz = z, tw = w;
    res.x = tx * m[0][0] + ty * m[1][0] + tz * m[2][0] + tw * m[3][0];
    res.y = tx * m[0][1] + ty * m[1][1] + tz * m[2][1] + tw * m[3][1];
    res.z = tx * m[0][2] + ty * m[1][2] + tz * m[2][2] + tw * m[3][2];
    res.w = tx * m[0][3] + ty * m[1][3] + tz * m[2][3] + tw * m[3][3];
    return res;
}