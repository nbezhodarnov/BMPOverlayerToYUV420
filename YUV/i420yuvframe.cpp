#include "i420yuvframe.h"

#include <stdexcept>

I420YUVFrame::I420YUVFrame(const std::vector<int8_t> data, const int &source_width, const int &source_height)
{
    if (data.size() != source_width * source_height) {
        throw std::runtime_error("I420YUVFrame: Wrong data size!");
    }

    width = source_width;
    height = source_height;

    int size = width * height;

    auto yBegin = data.begin();
    auto yEnd = yBegin + size;
    auto uBegin = yEnd;
    auto uEnd = uBegin + size / 4;
    auto vBegin = uEnd;
    auto vEnd = data.end();

    Y.insert(Y.begin(), yBegin, yEnd);
    U.insert(U.begin(), uBegin, uEnd);
    V.insert(V.begin(), vBegin, vEnd);
}
