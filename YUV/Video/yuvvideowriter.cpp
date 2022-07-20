#include "yuvvideowriter.h"

YUVVideoWriter::YUVVideoWriter(const std::string &filename)
{
    file.open(filename, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("YUVVideoWriter: Error while opening file!");
    }
}

void YUVVideoWriter::writeFrame(const std::unique_ptr<YUVFrame> &frame)
{
    std::vector<int8_t> data = frame->getData();
    if (!file.write(reinterpret_cast<char*>(&data[0]), data.size())) {
        throw std::runtime_error("YUVVideoWriter: Error while writing to file!");
    }
}
