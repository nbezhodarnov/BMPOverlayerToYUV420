#include "i420yuvframe.h"

#include <stdexcept>

I420YUVFrame::I420YUVFrame(const std::vector<int8_t> &data, const int &source_width, const int &source_height)
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

int32_t I420YUVFrame::getWidth() const
{
    return width;
}

int32_t I420YUVFrame::getHeight() const
{
    return height;
}

std::vector<int8_t> I420YUVFrame::getY() const
{
    return Y;
}

std::vector<int8_t> I420YUVFrame::getU() const
{
    return U;
}

std::vector<int8_t> I420YUVFrame::getV() const
{
    return V;
}

std::vector<int8_t> I420YUVFrame::getData() const
{
    std::vector<int8_t> data;
    data.insert(data.end(), Y.begin(), Y.end());
    data.insert(data.end(), U.begin(), U.end());
    data.insert(data.end(), V.begin(), V.end());
    return data;
}

void I420YUVFrame::overlayFrame(const std::unique_ptr<YUVFrame> &otherFrame, const int &leftOffset, const int &downOffset)
{
    if (otherFrame->getWidth() > width || otherFrame->getHeight() > height) {
        throw std::runtime_error("I420YUVFrame: Overlay frame is too big!");
    }

    if (otherFrame->getWidth() + leftOffset > width) {
        throw std::runtime_error("I420YUVFrame: leftOffset is too big!");
    }

    if (otherFrame->getHeight() + downOffset > height) {
        throw std::runtime_error("I420YUVFrame: downOffset is too big!");
    }

    std::vector<int8_t> otherY = otherFrame->getY();
    std::vector<int8_t> otherU = otherFrame->getU();
    std::vector<int8_t> otherV = otherFrame->getV();
    for (int i = downOffset; i < downOffset + otherFrame->getHeight(); i++) {
        for (int j = leftOffset; j < leftOffset + otherFrame->getWidth(); j++) {
            int otherI = i - downOffset;
            int otherJ = j - leftOffset;
            Y[i * width + j] = otherY[otherI * otherFrame->getWidth() + otherJ];
            U[(i >> 1) * width + j] = otherU[(otherI >> 1) * width + otherJ];
            V[(i >> 1) * width + j] = otherV[(otherI >> 1) * width + otherJ];
        }
    }
}
