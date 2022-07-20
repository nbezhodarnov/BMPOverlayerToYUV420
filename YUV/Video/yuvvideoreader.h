#ifndef YUVVIDEOREADER_H
#define YUVVIDEOREADER_H


#include <fstream>
#include <memory>
#include <string>

#include "../../filefunctions.h"
#include "../yuvframefactory.h"

class YUVVideoReader
{
public:
    YUVVideoReader(const std::string &filename, std::unique_ptr<YUVFrameFactory> &&newFrameFactory, const int &sourceWidth, const int &sourceHeight);
    bool eof() const;
    std::unique_ptr<YUVFrame> getFrame();

private:
    int32_t width, height;
    uint32_t bytesRead;
    uint32_t fileSize;
    std::ifstream file;
    std::unique_ptr<YUVFrameFactory> frameFactory;
};

#endif // YUVVIDEOREADER_H
