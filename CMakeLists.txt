cmake_minimum_required(VERSION 3.0.0)
project(kd_tree_app)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV 4 REQUIRED)
find_package(Boost 1.40.0 COMPONENTS filesystem system iostreams REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} include)

add_executable(${PROJECT_NAME} Examples/closest_point.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES})