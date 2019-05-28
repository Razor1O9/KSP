cmake_minimum_required(VERSION 3.14)
project(KSP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)
include_directories(.vs)
include_directories(cmake-build-debug)

add_executable(KSP
        .idea/.name
        .idea/KSP.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        .vs/ksp/v15/.suo
        .vs/slnx.sqlite
        .vs/VSWorkspaceState.json
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/KSP
        cmake-build-debug/KSP.cbp
        cmake-build-debug/KSP.exe
        cmake-build-debug/Makefile
        KSP.exe
        library.c
        library.h
        nja
        njvm
        njvm.c
        prog1.asm
        prog1.bin
        prog2.asm
        prog2.bin
        protofunctions.c
        protofunctions.h
        README.md)
