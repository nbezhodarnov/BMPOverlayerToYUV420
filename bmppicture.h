#ifndef BMPPICTURE_H
#define BMPPICTURE_H


#include <fstream>
#include <string>
#include <vector>

#include "filefunctions.h"
#include "rgbframe.h"

struct BitMapFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1, bfReserved2;
    uint32_t bfOffBits;
};

struct BitMapInfo {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImages;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

class BMPPicture
{
public:
    BMPPicture(const std::string &filename);

    RGBFrame getFrame() const;

private:
    BitMapFileHeader header;
    BitMapInfo info;
    std::vector<RGBPixel> data;

    void readHeader(std::ifstream &file);
    void readInfo(std::ifstream &file);
    void readData(std::ifstream &file);
};

#endif // BMPPICTURE_H
