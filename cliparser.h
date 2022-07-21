#ifndef CLIPARSER_H
#define CLIPARSER_H


#include <string>

struct Resolution {
    int width, height;
};

class CLIParser
{
public:
    CLIParser(int argc, char** argv);
    std::string getInputVideoFilename() const;
    int getInputVideoWidth() const;
    int getInputVideoHeight() const;
    std::string getInputBMPPictureFilename() const;
    std::string getOutputVideoFilename() const;
    int getLeftOffset() const;
    int getDownOffset() const;

private:
    std::string inputVideoFilename;
    int inputVideoWidth, inputVideoHeight;
    std::string inputBMPPictureFilename;
    std::string outputVideoFilename;
    int leftOffset, downOffset;

    Resolution parseResolution(const int &index, char** argv);
};

#endif // CLIPARSER_H
