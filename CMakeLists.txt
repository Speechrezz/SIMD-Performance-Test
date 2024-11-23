cmake_minimum_required(VERSION 3.27)
project(xsimd_test)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")

if (MSVC)
    add_compile_options(/arch:AVX2)
else()
    add_compile_options(-march=armv8-a)
endif()

add_executable(xsimd_test main.cpp
        VectorSineTest.h
        Timer.h)

if (APPLE)
    # Apple Accelerate framework
    find_library(ACCELERATE_FRAMEWORK Accelerate REQUIRED)
    target_link_libraries(xsimd_test PRIVATE ${ACCELERATE_FRAMEWORK})
endif()
