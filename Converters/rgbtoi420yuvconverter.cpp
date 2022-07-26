#include "rgbtoi420yuvconverter.h"

#include <stdexcept>
#include <cmath>

I420YUVFrame RGBToI420YUVConverter::convert(const RGBFrame &frame) const
{
    int frameSize = frame.width * frame.height;
    int UVComponentSize = frameSize / 4;

    std::vector<int8_t> yuv(frameSize * 3 / 2);
    int y, u, v;
    for (int i = 0; i < frame.height; i++) {
        bool extraLine = false;
        if (i == frame.height - 1 && frame.height % 2) {
            extraLine = true;
        }

        for (int j = 0; j < frame.width; j++) {
            int pixelIndex = i * frame.width + j;

            RGBPixel pixel = frame.data[pixelIndex];

            y = 0.257 * static_cast<uint8_t>(pixel.red) + 0.504 * static_cast<uint8_t>(pixel.green) + 0.098 * static_cast<uint8_t>(pixel.blue) + 16.0;
            u = -0.148 * static_cast<uint8_t>(pixel.red) - 0.291 * static_cast<uint8_t>(pixel.green) + 0.439 * static_cast<uint8_t>(pixel.blue) + 128.0;
            v = 0.439 * static_cast<uint8_t>(pixel.red) - 0.368 * static_cast<uint8_t>(pixel.green) - 0.071 * static_cast<uint8_t>(pixel.blue) + 128.0;

            // Right shift is used for dividing by 2
            int UVComponentI = (i >> 1) * (frame.width >> 1);
            int UVComponentJ = j >> 1;

            yuv[i * frame.width + j] = static_cast<int8_t>(y);
            if (!extraLine) {
                yuv[frameSize + UVComponentI + UVComponentJ] = static_cast<int8_t>(u);
                yuv[frameSize + UVComponentSize + UVComponentI + UVComponentJ] = static_cast<int8_t>(v);
            }
        }
    }
    return I420YUVFrame(yuv, frame.width, frame.height);
}
