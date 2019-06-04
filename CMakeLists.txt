cmake_minimum_required(VERSION 3.14)
project(KSP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)
include_directories(.vs)
include_directories(cmake-build-debug)

add_executable(KSP
        njvm.c
        protofunctions.c
        )
