#pragma once

struct Vec3 {
    float buf[3];

    Vec3(float x, float y, float z);

    float& operator[](int i);

    float operator[](int i) const;
};