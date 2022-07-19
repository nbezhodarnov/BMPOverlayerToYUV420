#ifndef I420YUVFRAME_H
#define I420YUVFRAME_H


#include "yuvframe.h"

#include <cstdint>
#include <vector>

class I420YUVFrame : public YUVFrame
{
public:
    I420YUVFrame(const std::vector<uint8_t> data, const int &source_width, const int &source_height);

private:
    int width, height;
    std::vector<uint8_t> Y;
    std::vector<uint8_t> U;
    std::vector<uint8_t> V;
};

#endif // I420YUVFRAME_H
