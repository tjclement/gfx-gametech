cmake_minimum_required(VERSION 3.3)
project(week1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    basic_midpoint/init.c
    basic_midpoint/init.h
    basic_midpoint/main.c
    basic_midpoint/mla.c
    basic_midpoint/mla.h
    triangle_rasterization/main.c
    triangle_rasterization/triangles.h
    triangle_rasterization/trirast.c
    triangle_rasterization/trirast.h
    triangle_rasterization/types.h)

add_executable(week1 ${SOURCE_FILES})