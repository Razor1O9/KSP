cmake_minimum_required(VERSION 3.14)
project(KSP C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(KSP
        library.c
        library.h
        njvm.c
        protofunctions.c
        protofunctions.h)
