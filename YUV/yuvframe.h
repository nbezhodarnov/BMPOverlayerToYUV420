#ifndef YUVFRAME_H
#define YUVFRAME_H


#include <memory>
#include <vector>

class YUVFrame
{
public:
    YUVFrame() = default;
    virtual int32_t getWidth() const = 0;
    virtual int32_t getHeight() const = 0;
    virtual std::vector<int8_t> getY() const = 0;
    virtual std::vector<int8_t> getU() const = 0;
    virtual std::vector<int8_t> getV() const = 0;
    virtual std::vector<int8_t> getData() const = 0;


    virtual void overlayFrame(const std::unique_ptr<YUVFrame> &otherFrame, const int &leftOffset, const int &downOffset) = 0;
    virtual ~YUVFrame() = default;
};

#endif // YUVFRAME_H
