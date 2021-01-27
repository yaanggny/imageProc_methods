cmake_minimum_required(VERSION 2.8)

project(VideoDenoiser)

set(SRC_demo main.cpp)

set(OpenCV_DIR "E:/Dev/DevPackages/opencv/v4.2.0/install_opencv4.2.0_vs2017_debug")

set(CMAKE_BUILD_TYPE Release)		#Change Release to Debug to switch the mode.

find_package(OpenCV REQUIRED)

set(inc_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE headers LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.hpp)
file(GLOB_RECURSE SRCS_view LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

source_group("inc" FILES ${headers})
source_group("src" FILES ${SRCS_view})

message(STATUS "SRCS_view=${SRCS_view}")
message(STATUS "headers=${headers}")

# add_subdirectory(src)

include_directories(${inc_dir})

add_executable(${PROJECT_NAME} ${headers} ${SRCS_view})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS}) # SRC_MODULE_static