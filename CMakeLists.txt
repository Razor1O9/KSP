cmake_minimum_required(VERSION 3.14)
project(KSP_hue)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)

add_executable(KSP_hue
        .idea/workspace.xml
        debug.txt
        KSP-HU1.TEAM
        mknjvm
        njvm
        njvm.c
        prog1.asm
        prog1.bin
        prog2.asm
        prog2.bin
        protofunctions.c
        protofunctions.h
        README.md)
