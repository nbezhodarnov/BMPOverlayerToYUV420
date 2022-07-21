#include "cliparser.h"

#include <stdexcept>

CLIParser::CLIParser(int argc, char **argv)
{
    if (argc < 5 || argc > 6) {
        throw std::runtime_error("CLIParser: Wrong arguments count!");
    }

    inputVideoFilename = std::string(argv[1]);

    Resolution videoResolution = parseResolution(2, argv);
    inputVideoWidth = videoResolution.width;
    inputVideoHeight = videoResolution.height;

    inputBMPPictureFilename = argv[3];

    outputVideoFilename = argv[4];

    if (argc == 5) {
        leftOffset = 0;
        downOffset = 0;
        return;
    }

    Resolution offset = parseResolution(5, argv);
    leftOffset = offset.width;
    downOffset = offset.height;
}

std::string CLIParser::getInputVideoFilename() const
{
    return inputVideoFilename;
}

int CLIParser::getInputVideoWidth() const
{
    return inputVideoWidth;
}

int CLIParser::getInputVideoHeight() const
{
    return inputVideoHeight;
}

std::string CLIParser::getInputBMPPictureFilename() const
{
    return inputBMPPictureFilename;
}

std::string CLIParser::getOutputVideoFilename() const
{
    return outputVideoFilename;
}

int CLIParser::getLeftOffset() const
{
    return leftOffset;
}

int CLIParser::getDownOffset() const
{
    return downOffset;
}

Resolution CLIParser::parseResolution(const int &index, char **argv)
{
    std::string firstNumber = "";
    int j = 0;
    for (; argv[index][j] != '\0' && argv[index][j] != 'x'; j++) {
        firstNumber.push_back(argv[index][j]);
    }

    if (argv[index][j] == '\0') {
        throw std::runtime_error("CLIParser: Wrong resolution format!");
    }
    j++;

    int width = std::stoi(firstNumber);
    if (width <= 0) {
        throw std::runtime_error("CLIParser: Wrong resolution format (width)!");
    }

    std::string secondNumber = "";
    for (; argv[index][j] != '\0' && argv[index][j] != 'x'; j++) {
        secondNumber.push_back(argv[index][j]);
    }

    int height = std::stoi(secondNumber);
    if (height <= 0) {
        throw std::runtime_error("CLIParser: Wrong resolution format (height)!");
    }

    return {width, height};
}
