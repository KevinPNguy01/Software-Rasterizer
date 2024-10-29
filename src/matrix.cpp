#include "matrix.hpp"

Vec3::Vec3(float x, float y, float z) : buf{ x, y, z } {}

float& Vec3::operator[](int i) {
    return buf[i];
}

float Vec3::operator[](int i) const {
    return buf[i];
}