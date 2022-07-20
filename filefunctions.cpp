#include "filefunctions.h"

uint32_t getFileSize(std::ifstream &file)
{
    uint32_t currentPoint = file.tellg();

    file.seekg(0, std::ios_base::end);
    uint32_t fileSize = file.tellg();

    file.seekg(currentPoint, std::ios_base::beg);

    return fileSize;
}
