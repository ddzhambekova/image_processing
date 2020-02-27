cmake_minimum_required(VERSION 3.0)

project(gradient_rect)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(gradient_rect gradient_rect.cpp)
target_link_libraries(gradient_rect ${OpenCV_LIBS})