cmake_minimum_required(VERSION 3.12)
project(ksp C)

set(CMAKE_C_STANDARD 90)

add_library(ksp library.c library.h njvm.c protofunctions.h)