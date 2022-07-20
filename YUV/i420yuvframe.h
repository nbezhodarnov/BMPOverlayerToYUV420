#ifndef I420YUVFRAME_H
#define I420YUVFRAME_H


#include "yuvframe.h"

#include <cstdint>
#include <vector>

class I420YUVFrame : public YUVFrame
{
public:
    I420YUVFrame(const std::vector<int8_t> &data, const int &source_width, const int &source_height);
    int32_t getWidth() const override;
    int32_t getHeight() const override;
    std::vector<int8_t> getY() const override;
    std::vector<int8_t> getU() const override;
    std::vector<int8_t> getV() const override;
    std::vector<int8_t> getData() const override;

    void overlayFrame(const std::unique_ptr<YUVFrame> &otherFrame, const int &leftOffset, const int &downOffset) override;

private:
    int width, height;
    std::vector<int8_t> Y;
    std::vector<int8_t> U;
    std::vector<int8_t> V;
};

#endif // I420YUVFRAME_H
