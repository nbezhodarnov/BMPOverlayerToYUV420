#include "yuvvideoreader.h"

YUVVideoReader::YUVVideoReader(const std::string &filename, std::unique_ptr<YUVFrameFactory> &&newFrameFactory, const int &sourceWidth, const int &sourceHeight)
{
    file.open(filename, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("YUVVideoReader: Error while opening file!");
    }

    width = sourceWidth;
    height = sourceHeight;

    uint32_t fileSize = getFileSize(file);
    double framesCount = static_cast<double>(fileSize) / static_cast<double>(width * height);
    if (framesCount - static_cast<uint32_t>(framesCount) > 0.001) {
        throw std::runtime_error("YUVVideoReader: Wrong resolution!");
    }

    frameFactory = std::move(newFrameFactory);
}

bool YUVVideoReader::eof() const
{
    return file.eof();
}

std::unique_ptr<YUVFrame> YUVVideoReader::getFrame()
{
    if (eof()) {
        return nullptr;
    }

    uint32_t frameSize = frameFactory->calculateFrameSize(width, height);
    std::vector<int8_t> frameData(frameSize);

    if (!file.read(reinterpret_cast<char*>(&frameData[0]), frameSize)) {
        throw std::runtime_error("YUVVideoReader: Error while reading data!");
    }

    return frameFactory->createFrame(frameData, width, height);
}
