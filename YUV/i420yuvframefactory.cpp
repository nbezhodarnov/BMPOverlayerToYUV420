#include "i420yuvframefactory.h"

std::unique_ptr<YUVFrame> I420YUVFrameFactory::createFrame(const std::vector<int8_t> data, const int &source_width, const int &source_height) const
{
    return std::unique_ptr<YUVFrame>(new I420YUVFrame(data, source_width, source_height));
}

uint32_t I420YUVFrameFactory::calculateFrameSize(const int &source_width, const int &source_height) const
{
    return source_width * source_height * 3 / 2;
}
