#include "bmppicture.h"

const int headerAndInfoSize = 54;
const int infoSize = 40;
const int BM = 0x4D42;
const int BI_RGB = 0;
const int RGBPixelSize = 24;

BMPPicture::BMPPicture(const std::string &filename)
{
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("BMPPicture: Error while opening file!");
    }

    readHeader(file);
    readInfo(file);
    readData(file);
}

RGBFrame BMPPicture::getFrame() const
{
    return {info.biWidth, info.biHeight, data};
}

uint32_t BMPPicture::getFileSize(std::ifstream &file)
{
    uint32_t currentPoint = file.tellg();

    file.seekg(0, std::ios_base::end);
    uint32_t fileSize = file.tellg();

    file.seekg(currentPoint, std::ios_base::beg);

    return fileSize;
}

void BMPPicture::readHeader(std::ifstream &file)
{
    uint32_t fileSize = getFileSize(file);

    if (fileSize <= headerAndInfoSize) {
        throw std::runtime_error("BMPPicture: Size of the file is less than required!");
    }

    file.read(reinterpret_cast<char*>(&header.bfType), sizeof(header.bfType));

    if (header.bfType != BM) {
        throw std::runtime_error("BMPPicture: Wrong bmp file format!");
    }

    file.read(reinterpret_cast<char*>(&header.bfSize), sizeof(header.bfSize));

    if (header.bfSize != fileSize) {
        throw std::runtime_error("BMPPicture: header.bfSize differs from actual size of a file!");
    }

    file.read(reinterpret_cast<char*>(&header.bfReserved1), sizeof(header.bfReserved1));
    file.read(reinterpret_cast<char*>(&header.bfReserved2), sizeof(header.bfReserved2));
    file.read(reinterpret_cast<char*>(&header.bfOffBits), sizeof(header.bfOffBits));
}

void BMPPicture::readInfo(std::ifstream &file)
{
    file.read(reinterpret_cast<char*>(&info.biSize), sizeof(info.biSize));

    if (info.biSize != infoSize) {
        throw std::runtime_error("BMPPicture: Not supported BITMAPCOREHEADER, BITMAPV4HEADER and BITMAPV5HEADER!");
    }

    file.read(reinterpret_cast<char*>(&info.biWidth), sizeof(info.biWidth));
    file.read(reinterpret_cast<char*>(&info.biHeight), sizeof(info.biHeight));
    file.read(reinterpret_cast<char*>(&info.biPlanes), sizeof(info.biPlanes));
    file.read(reinterpret_cast<char*>(&info.biBitCount), sizeof(info.biBitCount));

    if (info.biBitCount != RGBPixelSize) {
        throw std::runtime_error("BMPPicture: Not supported info.biBitCount other than 24!");
    }

    file.read(reinterpret_cast<char*>(&info.biCompression), sizeof(info.biCompression));

    if (info.biCompression != BI_RGB) {
        throw std::runtime_error("BMPPicture: Not supported info.biCompression other than BI_RGB!");
    }

    file.read(reinterpret_cast<char*>(&info.biSizeImages), sizeof(info.biSizeImages));
    file.read(reinterpret_cast<char*>(&info.biXPelsPerMeter), sizeof(info.biXPelsPerMeter));
    file.read(reinterpret_cast<char*>(&info.biYPelsPerMeter), sizeof(info.biYPelsPerMeter));
    file.read(reinterpret_cast<char*>(&info.biClrUsed), sizeof(info.biClrUsed));

    if (info.biClrUsed) {
        throw std::runtime_error("BMPPicture: Not supported color table!");
    }

    file.read(reinterpret_cast<char*>(&info.biClrImportant), sizeof(info.biClrImportant));
}

void BMPPicture::readData(std::ifstream &file)
{
    const int bytesPerLine = ((info.biWidth * info.biBitCount + 31) >> 5) << 2;
    const int skip = 4 - ((info.biWidth * info.biBitCount) >> 3) & 3;

    int pixelsToRead = bytesPerLine / 3;
    int pixelsToSkip = 0;
    if (skip) {
        pixelsToRead++;
        pixelsToSkip = 1;
    }

    int i = 0;
    for (; !file.eof() && i < std::abs(info.biHeight); i++) {
        std::vector<RGBPixel> line(pixelsToRead);
        file.read(reinterpret_cast<char*>(&line[0]), bytesPerLine);
        data.insert(data.begin(), line.begin(), line.end() - pixelsToSkip);
    }

    if (i < std::abs(info.biHeight)) {
        throw std::runtime_error("BMPPicture: There are not enought lines!");
    }
}
