#ifndef RGBFRAME_H
#define RGBFRAME_H


#include <cstdint>
#include <vector>

struct RGBPixel {
    int8_t blue;
    int8_t green;
    int8_t red;
};

struct RGBFrame {
    int width, height;
    std::vector<RGBPixel> data;
};

#endif // RGBFRAME_H
