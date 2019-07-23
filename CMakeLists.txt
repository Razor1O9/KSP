cmake_minimum_required(VERSION 3.14)
project(KSP C)

set(CMAKE_C_STANDARD 11)
add_library (bigint libbigint.a)
set(SOURCE_FILES bigint/build/include/bigint.h bigint/build/include/support.h bigint/build/lib/libbigint.a)
set_target_properties(bigint PROPERTIES LINKER_LANGUAGE C)

include_directories(.)

add_executable(KSP
        njvm.c
        protofunctions.c
        ${SOURCE_FILES}
        )
