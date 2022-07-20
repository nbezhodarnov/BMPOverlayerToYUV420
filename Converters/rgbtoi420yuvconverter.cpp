#include "rgbtoi420yuvconverter.h"

I420YUVFrame RGBToI420YUVConverter::convert(const RGBFrame &frame) const
{
    int size = frame.width * frame.height;

    std::vector<int8_t> yuv(size * 3 / 2);
    int y, u, v;
    for (int i = 0; i < frame.height; i++) {
        for (int j = 0; j < frame.width; j++) {
            RGBPixel pixel = frame.data[i * frame.width + j];

            y = ((66 * pixel.red + 129 * pixel.green + 25 * pixel.blue + 128) >> 8) + 16;
            u = ((-38 * pixel.red - 74 * pixel.green + 112 * pixel.blue + 128) >> 8) + 128;
            v = ((112 * pixel.red - 94 * pixel.green - 18 * pixel.blue + 128) >> 8) + 128;

            uint8_t yByte = y < 16 ? 16 : (y > 255 ? 255 : y);
            uint8_t uByte = u < 0 ? 0 : (u > 255 ? 255 : u);
            uint8_t vByte = v < 0 ? 0 : (v > 255 ? 255 : v);

            yuv[i * frame.width + j] = static_cast<int8_t>(yByte);
            yuv[size + (i >> 1) * frame.width + j] = static_cast<int8_t>(uByte);
            yuv[size * 5 / 4 + (i >> 1) * frame.width + j] = static_cast<int8_t>(vByte);
        }
    }
    return I420YUVFrame(yuv, frame.width, frame.height);
}
