cmake_minimum_required(VERSION 3.14)
project(KSP C)

set(CMAKE_C_STANDARD 11)
include_directories(.)

add_library (bigint STATIC
        bigint/build/include/bigint.h
        bigint/build/include/support.h)
set_target_properties(bigint PROPERTIES LINKER_LANGUAGE C)
add_executable(KSP
        njvm.c
        protofunctions.c
        bigint/tst/support.c
        bigint/src/bigint.c
        )
target_link_libraries(KSP LINK_PRIVATE bigint)