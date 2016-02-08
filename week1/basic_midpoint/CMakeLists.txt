cmake_minimum_required(VERSION 3.3)
project(basic_midpoint)

#find_package(SDL)
#target_include_directories(basic_midpoint ${SDL2_INCLUDE_DIR})
#target_link_libraries(basic_midpoint ${SDL2_LIBRARY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    init.c
    init.h
    main.c
    Makefile
    mla.c
    mla.h)

add_executable(basic_midpoint ${SOURCE_FILES})

include(FindPkgConfig)

PKG_SEARCH_MODULE(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})
target_link_libraries (basic_midpoint ${SDL_LIBRARY})
