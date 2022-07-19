#ifndef I420YUVFRAMEFACTORY_H
#define I420YUVFRAMEFACTORY_H

#include "yuvframefactory.h"
#include "i420yuvframe.h"

class I420YUVFrameFactory : public YUVFrameFactory
{
public:
    I420YUVFrameFactory() = default;
    std::unique_ptr<YUVFrame> createFrame(const std::vector<uint8_t> data, const int &source_width, const int &source_height) const override;
};

#endif // I420YUVFRAMEFACTORY_H
