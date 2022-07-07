cmake_minimum_required(VERSION 3.0.0)
project(kd_tree_app)

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} closest_point.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})