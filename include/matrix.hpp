#pragma once

struct Vec3 {
    float buf[3];

    Vec3(float x, float y, float z);

    float& operator[](int i);

    float operator[](int i) const;
};

struct Vec4 {
    float buf[4];

    Vec4(float x, float y, float z, float w);

    float& operator[](int i);

    float operator[](int i) const;
};

struct Mat4 {
    static void mul(Mat4& dest, const Mat4& a, const Mat4& b);

    float buf[4][4];

    Mat4(float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);

    float* operator[](int i);
};