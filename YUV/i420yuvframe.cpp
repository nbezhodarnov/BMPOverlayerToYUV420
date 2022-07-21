#include "i420yuvframe.h"

#include <stdexcept>

I420YUVFrame::I420YUVFrame(const std::vector<int8_t> &data, const int &source_width, const int &source_height)
{
    if (data.size() != source_width * source_height * 3 / 2) {
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
        bool extraLine = false;
        if (i == height - 1 && height % 2) {
            extraLine = true;
        }

        for (int j = leftOffset; j < leftOffset + otherFrame->getWidth(); j++) {
            int otherI = i - downOffset;
            int otherJ = j - leftOffset;

            bool extraLineOther = false;
            if (otherI == otherFrame->getHeight() - 1 && otherFrame->getHeight() % 2) {
                extraLineOther = true;
            }

            // Right shift is used for dividing by 2
            int UVComponentI = (i >> 1) * (width >> 1);
            int UVComponentJ = j >> 1;
            int otherUVComponentI = (otherI >> 1) * (otherFrame->getWidth() >> 1);
            int otherUVComponentJ = otherJ >> 1;

            Y[i * width + j] = otherY[otherI * otherFrame->getWidth() + otherJ];
            if (!extraLine && !extraLineOther) {
                U[UVComponentI + UVComponentJ] = otherU[otherUVComponentI + otherUVComponentJ];
                V[UVComponentI + UVComponentJ] = otherV[otherUVComponentI + otherUVComponentJ];
            }
        }
    }
}
