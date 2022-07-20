#ifndef YUVFRAMEFACTORY_H
#define YUVFRAMEFACTORY_H


#include "yuvframe.h"

#include <cstdint>
#include <memory>
#include <vector>

class YUVFrameFactory {
public:
    YUVFrameFactory() = default;
    virtual std::unique_ptr<YUVFrame> createFrame(const std::vector<int8_t> data, const int &source_width, const int &source_height) const = 0;
    virtual uint32_t calculateFrameSize(const int &source_width, const int &source_height) const = 0;
    virtual ~YUVFrameFactory() = default;
};

#endif // YUVFRAMEFACTORY_H
