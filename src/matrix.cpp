#include "matrix.hpp"

Vec3::Vec3(float x, float y, float z) : buf{ x, y, z } {}

float& Vec3::operator[](int i) {
    return buf[i];
}

float Vec3::operator[](int i) const {
    return buf[i];
}

Vec4::Vec4(float x, float y, float z, float w) : buf{ x, y, z, w} {}

float& Vec4::operator[](int i) {
    return buf[i];
}

float Vec4::operator[](int i) const {
    return buf[i];
}

Mat4::Mat4(float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33) {
    buf[0][0] = m00; buf[0][1] = m01; buf[0][2] = m02; buf[0][3] = m03;
    buf[1][0] = m10; buf[1][1] = m11; buf[1][2] = m12; buf[1][3] = m13;
    buf[2][0] = m20; buf[2][1] = m21; buf[2][2] = m22; buf[2][3] = m23;
    buf[3][0] = m30; buf[3][1] = m31; buf[3][2] = m32; buf[3][3] = m33;
}

float* Mat4::operator[](int i) {
    return buf[i];
}