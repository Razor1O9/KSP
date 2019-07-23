cmake_minimum_required(VERSION 3.14)
project(KSP C)

set(CMAKE_C_STANDARD 11)
add_library (bigint bigint/build/include/bigint.h bigint/build/include/support.h libbigint.a)
set_target_properties(bigint PROPERTIES LINKER_LANGUAGE C)

include_directories(.)

add_executable(KSP
        njvm.c
        protofunctions.c
        )

find_library(BIGINT_LIB bigint)
target_link_libraries(KSP LINK_PUBLIC ${BIGINT_LIB})
