cmake_minimum_required(VERSION 3.5)

project(BMPInserterToYUV420 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BMPInserterToYUV420 main.cpp bmppicture.h bmppicture.cpp)
