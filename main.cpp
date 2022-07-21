#include <iostream>

#include "Converters/rgbtoi420yuvconverter.h"
#include "YUV/Video/yuvvideoreader.h"
#include "YUV/Video/yuvvideowriter.h"
#include "YUV/i420yuvframefactory.h"
#include "bmppicture.h"
#include "cliparser.h"

int main(int argc, char** argv)
{
    CLIParser parser(argc, argv);
    std::string inputVideoFilename = parser.getInputVideoFilename();
    int inputVideoWidth = parser.getInputVideoWidth();
    int inputVideoHeight = parser.getInputVideoHeight();
    std::string inputBMPPictureFilename = parser.getInputBMPPictureFilename();
    std::string outputVideoFilename = parser.getOutputVideoFilename();
    int leftOffset = parser.getLeftOffset();
    int downOffset = parser.getDownOffset();

    BMPPicture bmp(inputBMPPictureFilename);

    RGBToI420YUVConverter converter;
    std::unique_ptr<YUVFrame> convertedBMP(new I420YUVFrame(converter.convert(bmp.getFrame())));

    YUVVideoReader reader(inputVideoFilename, std::unique_ptr<YUVFrameFactory>(new I420YUVFrameFactory()), inputVideoWidth, inputVideoHeight);
    YUVVideoWriter writer(outputVideoFilename);

    while (!reader.eof()) {
        std::unique_ptr<YUVFrame> frame = reader.getFrame();
        frame->overlayFrame(convertedBMP, leftOffset, downOffset);
        writer.writeFrame(frame);
    }

    return 0;
}
