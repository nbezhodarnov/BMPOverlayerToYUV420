cmake_minimum_required(VERSION 3.5)

project(BMPInserterToYUV420 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BMPInserterToYUV420 main.cpp rgbframe.h bmppicture.h bmppicture.cpp YUV/yuvframe.h YUV/i420yuvframe.h YUV/i420yuvframe.cpp YUV/yuvframefactory.h YUV/i420yuvframefactory.h YUV/i420yuvframefactory.cpp Converters/rgbtoi420yuvconverter.h Converters/rgbtoi420yuvconverter.cpp filefunctions.h filefunctions.cpp YUV/Video/yuvvideoreader.h YUV/Video/yuvvideoreader.cpp)
