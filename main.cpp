#include <iostream>

#include "Converters/rgbtoi420yuvconverter.h"
#include "YUV/Video/yuvvideoreader.h"
#include "YUV/Video/yuvvideowriter.h"
#include "YUV/i420yuvframefactory.h"
#include "bmppicture.h"

int main()
{
    BMPPicture bmp("a64af8df595accac8c2f8bc2f407f7e3.bmp");

    RGBToI420YUVConverter converter;
    std::unique_ptr<YUVFrame> convertedBMP(new I420YUVFrame(converter.convert(bmp.getFrame())));

    YUVVideoReader reader("park_joy_1080p50.yuv", std::unique_ptr<YUVFrameFactory>(new I420YUVFrameFactory()), 1920, 1080);
    YUVVideoWriter writer("park_joy_1080p50_overlayed.yuv");

    while (!reader.eof()) {
        std::unique_ptr<YUVFrame> frame = reader.getFrame();
        frame->overlayFrame(convertedBMP, 0, 0);
        writer.writeFrame(frame);
    }

    return 0;
}
