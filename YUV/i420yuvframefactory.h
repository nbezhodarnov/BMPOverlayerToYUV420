#ifndef I420YUVFRAMEFACTORY_H
#define I420YUVFRAMEFACTORY_H

#include "yuvframefactory.h"
#include "i420yuvframe.h"

class I420YUVFrameFactory : public YUVFrameFactory
{
public:
    I420YUVFrameFactory() = default;
    std::unique_ptr<YUVFrame> createFrame(const std::vector<int8_t> data, const int &sourceWidth, const int &sourceHeight) const override;
    uint32_t calculateFrameSize(const int &sourceWidth, const int &sourceHeight) const override;
};

#endif // I420YUVFRAMEFACTORY_H
