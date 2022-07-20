#ifndef RGBTOI420YUVCONVERTER_H
#define RGBTOI420YUVCONVERTER_H


#include "../YUV/i420yuvframe.h"
#include "../rgbframe.h"

class RGBToI420YUVConverter
{
public:
    RGBToI420YUVConverter() = default;
    I420YUVFrame convert(const RGBFrame &frame) const;
};

#endif // RGBTOI420YUVCONVERTER_H
