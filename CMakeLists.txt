cmake_minimum_required(VERSION 3.10)
project(opc)
add_subdirectory(src)

# set( CMAKE_BUILD_TYPE "Release" )
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
