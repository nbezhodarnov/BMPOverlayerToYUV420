#include "i420yuvframefactory.h"

std::unique_ptr<YUVFrame> I420YUVFrameFactory::createFrame(const std::vector<int8_t> data, const int &sourceWidth, const int &sourceHeight) const
{
    return std::unique_ptr<YUVFrame>(new I420YUVFrame(data, sourceWidth, sourceHeight));
}

uint32_t I420YUVFrameFactory::calculateFrameSize(const int &sourceWidth, const int &sourceHeight) const
{
    return sourceWidth * sourceHeight * 3 / 2;
}
