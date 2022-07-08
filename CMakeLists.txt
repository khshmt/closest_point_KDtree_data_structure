cmake_minimum_required(VERSION 3.0.0)
project(kd_tree_app)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} include)
# add_library(kdtree src/kdtree.hpp)

add_executable(${PROJECT_NAME} Examples/closest_point.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})