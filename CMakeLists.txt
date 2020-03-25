cmake_minimum_required(VERSION 2.8.3)
project(ros_bridge_test)

find_package(catkin REQUIRED)
find_package(catkin_simple REQUIRED)
catkin_simple(ALL_DEPS_REQUIRED)

add_definitions(-std=c++17)
set(CMAKE_BUILD_TYPE Release)

find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

cs_add_library(${PROJECT_NAME}_lib src/ros_image_pub.cpp)
target_link_libraries(${PROJECT_NAME}_lib ${OpenCV_LIBRARIES} ${catkin_LIBRARIES})

cs_add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}_node.cpp)
target_link_libraries(${PROJECT_NAME}_node ${PROJECT_NAME}_lib)


cs_install()
cs_export()