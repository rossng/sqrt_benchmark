cmake_minimum_required(VERSION 3.1)
project(sqrt_benchmark)

add_compile_options(-std=c99 -Wall -O0)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(sqrt_benchmark sqrt_benchmark.c)
target_link_libraries(sqrt_benchmark m)
set_property(TARGET sqrt_benchmark PROPERTY C_STANDARD 99)
