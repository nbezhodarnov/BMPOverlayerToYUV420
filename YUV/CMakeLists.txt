set(YUV_LIBRARY_HEADERS yuvframe.h i420yuvframe.h yuvframefactory.h i420yuvframefactory.h Video/yuvvideoreader.h Video/yuvvideowriter.h)
set(YUV_LIBRARY_SOURCES i420yuvframe.cpp i420yuvframefactory.cpp Video/yuvvideoreader.cpp Video/yuvvideowriter.cpp)

add_library(yuv SHARED)
target_sources(yuv PRIVATE "${YUV_LIBRARY_SOURCES}" PUBLIC FILE_SET HEADERS BASE_DIRS "${PROJECT_SOURCE_DIR}" FILES "${YUV_LIBRARY_HEADERS}")
target_link_libraries(yuv filefunctions)
