cmake_minimum_required(VERSION 3.2)
project(xsimd_test)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")

add_executable(xsimd_test main.cpp
        VectorSineTest.h
        Timer.h)

# Find the Accelerate framework
find_library(ACCELERATE_FRAMEWORK Accelerate REQUIRED)
target_link_libraries(xsimd_test PRIVATE ${ACCELERATE_FRAMEWORK})


if (MSVC)
    add_compile_options(/arch:AVX2)
else()
    #add_compile_options(-mneon)
    add_compile_options(-march=armv8-a)
endif()