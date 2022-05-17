cmake_minimum_required(VERSION 3.18)
project(opc)
add_subdirectory(src)

set( CMAKE_BUILD_TYPE "Debug" )
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# set(CMAKE_CXX_FLAGS "-DGEN_DEBUG ${CMAKE_CXX_FLAGS}")