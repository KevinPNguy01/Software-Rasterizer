#include <Windows.h>

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

void RenderFrame(HWND hwnd, HDC hdcMem, int width, int height) {
    HDC hdcDest = GetDC(hwnd);
    // Update only necessary pixels in bits[] here

    // BitBlt once to draw the entire frame
    BitBlt(hdcDest, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

    ReleaseDC(hwnd, hdcDest);
}

void RenderTriangle(void* bits) {

}

int main()
{
    HWND hwnd = GetConsoleWindow();
    HDC hdcDest = GetDC(GetConsoleWindow());

    const int width = 100;
    const int height = 100;

    // Create a BITMAPINFO structure for a DIB
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;  // Negative to make the image top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;  // 32-bit color depth
    bmi.bmiHeader.biCompression = BI_RGB;

    // Create once at program startup
    void* bits;
    HBITMAP hBitmap = CreateDIBSection(hdcDest, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);

    // Assuming width and height are defined for your bitmap
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calculate the pixel index for 32-bit color
            int index = y * width + x;
            ((DWORD*)bits)[index] = RGB(0, 0, 255); // Set pixel to red
        }
    }

    HDC hdcMem = CreateCompatibleDC(hdcDest);
    SelectObject(hdcMem, hBitmap);

    RenderFrame(hwnd, hdcMem, width, height);
    while (1) {

    }
}