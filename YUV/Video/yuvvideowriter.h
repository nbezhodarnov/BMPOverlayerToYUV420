#ifndef YUVVIDEOWRITER_H
#define YUVVIDEOWRITER_H


#include <fstream>
#include <memory>
#include <string>

#include "../yuvframe.h"

class YUVVideoWriter
{
public:
    YUVVideoWriter(const std::string &filename);
    void writeFrame(const std::unique_ptr<YUVFrame> &frame);

private:
    std::ofstream file;
};

#endif // YUVVIDEOWRITER_H
