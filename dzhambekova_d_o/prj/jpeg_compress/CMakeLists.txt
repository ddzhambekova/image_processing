cmake_minimum_required(VERSION 3.0)

project(jpeg_compress)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(jpeg_compress jpeg_compress.cpp)
target_link_libraries(jpeg_compress ${OpenCV_LIBS})