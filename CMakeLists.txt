cmake_minimum_required(VERSION 3.23)

project(BMPOverlayerToYUV420 LANGUAGES CXX)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FILEFUNCTIONS_LIBRARY_HEADERS filefunctions.h)
set(FILEFUNCTIONS_LIBRARY_SOURCES filefunctions.cpp)

add_library(filefunctions SHARED "${FILEFUNCTIONS_LIBRARY_HEADERS}" "${FILEFUNCTIONS_LIBRARY_SOURCES}")
target_include_directories(filefunctions PRIVATE "${PROJECT_SOURCE_DIR}")

set(RGB_LIBRARY_HEADERS rgbframe.h)

set(BMP_LIBRARY_HEADERS bmppicture.h)
set(BMP_LIBRARY_SOURCES bmppicture.cpp)

add_library(bmp SHARED "${BMP_LIBRARY_HEADERS}" "${BMP_LIBRARY_SOURCES}")
target_include_directories(bmp PRIVATE "${PROJECT_SOURCE_DIR}")
target_link_libraries(bmp filefunctions)

add_subdirectory("YUV")

add_subdirectory("Converters")

add_executable(BMPOverlayerToYUV420 cliparser.h cliparser.cpp main.cpp)
target_link_libraries(BMPOverlayerToYUV420 PRIVATE bmp yuv converters)

install(TARGETS bmp filefunctions yuv converters FILE_SET HEADERS)
