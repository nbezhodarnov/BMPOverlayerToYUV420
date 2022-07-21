set(CONVERTERS_LIBRARY_HEADERS rgbtoi420yuvconverter.h)
set(CONVERTERS_LIBRARY_SOURCES rgbtoi420yuvconverter.cpp)

add_library(converters SHARED)
target_sources(converters PRIVATE "${CONVERTERS_LIBRARY_SOURCES}" PUBLIC FILE_SET HEADERS BASE_DIRS "${PROJECT_SOURCE_DIR}" FILES "${CONVERTERS_LIBRARY_HEADERS}")
target_link_libraries(converters yuv)
