#include "i420yuvframefactory.h"

std::unique_ptr<YUVFrame> I420YUVFrameFactory::createFrame(const std::vector<uint8_t> data, const int &source_width, const int &source_height) const
{
    return std::unique_ptr<YUVFrame>(new I420YUVFrame(data, source_width, source_height));
}
