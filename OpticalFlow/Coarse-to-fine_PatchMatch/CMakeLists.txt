cmake_minimum_required(VERSION 2.6)
SET(PROJ_NAME CPM)
PROJECT (${PROJ_NAME})

add_definitions(-DWITH_SSE)

if(MSVC)
    if(DEFINED CMAKE_CONFIGURATION_TYPES)
        string(TOLOWER ${CMAKE_CONFIGURATION_TYPES} build_type)
    elseif(DEFINED CMAKE_BUILD_TYPE)      
        string(TOLOWER ${CMAKE_CONFIGURATION_TYPES} build_type)   
    endif()

    if(build_type MATCHES "debug")
        set(OpenCV_DIR "E:/Dev/DevPackages/opencv/v4.2.0/install_opencv4.2.0_vs2017_debug")
    else()
        set(OpenCV_DIR "E:/Dev/DevPackages/opencv/v4.2.0/install_opencv4.2.0_vs2017_R")
    endif()
    set(OpenCV_DIR "E:/Dev/DevPackages/opencv/v4.2.0/install_opencv4.2.0_vs2017")
    message(STATUS "build_type=${CMAKE_CONFIGURATION_TYPES}")
endif(MSVC)

find_package(OpenCV REQUIRED)
include_directories(./inc)

aux_source_directory(${CMAKE_SOURCE_DIR} SRCS)

set(headers_files "")
if(MSVC)
    file(GLOB headers1 LIST_DIRECTORIES false RELATIVE ${CMAKE_SOURCE_DIR} inc/*.h inc/*.hpp)
    file(GLOB headers2 LIST_DIRECTORIES false RELATIVE ${CMAKE_SOURCE_DIR} *.h *.hpp)
    string(JOIN ";" headers ${headers1} ${headers2})

    source_group("inc" FILES ${headers})
    source_group("src" FILES ${SRCS})  
    set(headers_files ${headers})  
endif(MSVC)

add_executable(${PROJ_NAME} ${SRCS} ${headers_files})
target_link_libraries(${PROJ_NAME} ${OpenCV_LIBS})
