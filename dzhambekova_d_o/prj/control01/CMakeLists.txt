cmake_minimum_required(VERSION 3.0)

project(control01)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(control01 control01.cpp)
target_link_libraries(control01 ${OpenCV_LIBS})