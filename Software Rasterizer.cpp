#include <Windows.h>
#include <cmath>
#include <iostream>

const int screenWidth = 400;
const int screenHeight = 400;

struct Vec3 {
    float buf[3];
    Vec3(float x, float y, float z) : buf{x, y, z} {};

    float& operator[](int i) {
        return buf[i];
    }

    float operator[](int i) const {
        return buf[i];
    }
};

void RenderFrame(HWND hwnd, HDC hdcMem) {
    HDC hdcDest = GetDC(hwnd);
    BitBlt(hdcDest, 0, 0, screenWidth, screenHeight, hdcMem, 0, 0, SRCCOPY);
    ReleaseDC(hwnd, hdcDest);
}

bool InsideHalfPlane(const Vec3& v0, const Vec3& v1, const Vec3& p) {
    return (v0[1] - v1[1]) * (p[0] - v0[0]) + (v1[0] - v0[0]) * (p[1] - v0[1]) > 0;
}

bool InsideTriangle(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& p) {
    return 
        InsideHalfPlane(v0, v1, p) &&
        InsideHalfPlane(v1, v2, p) &&
        InsideHalfPlane(v2, v0, p);
}

COLORREF RGBtoBGR(COLORREF color) {
    BYTE red = GetRValue(color);
    BYTE green = GetGValue(color);
    BYTE blue = GetBValue(color);

    return RGB(blue, green, red);
}

void DrawTriangle(void* bits, const Vec3& v0, const Vec3& v1, const Vec3& v2, COLORREF color) {
    int width = ceil(screenWidth * (max(v0[0], max(v1[0], v2[0])) - min(v0[0], min(v1[0], v2[0]))));
    int height = ceil(screenHeight * (max(v0[1], max(v1[1], v2[1])) - min(v0[1], min(v1[1], v2[1]))));

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (InsideTriangle(v0, v1, v2, Vec3(((float)x + 0.5) / width, ((float)y + 0.5) / height, 0))) {
                ((DWORD*)bits)[y * screenWidth + x] = RGBtoBGR(color);
            }
        }
    }
}

void DrawTriangle(void* bits, const Vec3& v0, const Vec3& v1, const Vec3& v2) {
    DrawTriangle(bits, v0, v1, v2, RGB(255, 255, 255));
}

int main()
{
    HWND hwnd = GetConsoleWindow();
    HDC hdcDest = GetDC(GetConsoleWindow());

    // Create a BITMAPINFO structure for a DIB
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = screenWidth;
    bmi.bmiHeader.biHeight = -screenHeight;  // Negative to make the image top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;  // 32-bit color depth
    bmi.bmiHeader.biCompression = BI_RGB;

    // Create once at program startup
    void* bits;
    HBITMAP hBitmap = CreateDIBSection(hdcDest, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    HDC hdcMem = CreateCompatibleDC(hdcDest);
    SelectObject(hdcMem, hBitmap);

    DrawTriangle(bits, Vec3(0, 0, 0), Vec3(1, 0.5, 0), Vec3(0.5, 1, 0), RGB(0, 0, 255));
    while (1) {
        RenderFrame(hwnd, hdcMem);
    }
}