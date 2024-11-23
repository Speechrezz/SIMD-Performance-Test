//
// Created by Mark Muranov on 11/22/24.
//

#pragma once

#include "xsimd/xsimd.hpp"

void fillArray(float* array, size_t length)
{
    for (size_t i = 0; i < length; ++i)
        array[i] = static_cast<float>(i);
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <immintrin.h>
void vectorSineAvx(const float* input, float* output, size_t length)
{
    for (size_t i = 0; i < length; i += 8)
    {
        __m256 in = _mm256_load_ps(input + i);
        in = _mm256_sin_ps(in);
        _mm256_store_ps(output + i, in);
    }
}
#elif defined(__APPLE__)
#include "Accelerate/Accelerate.h"
void vectorSineAccelerate(const float* input, float* output, size_t length)
{
    const int lengthInt = static_cast<int>(length);
    vvsinf(output, input, &lengthInt);
}
#endif


void vectorSineXsimd(const float* input, float* output, size_t length)
{
    using Batch = xsimd::batch<float, xsimd::best_arch>;
    const size_t inc = Batch::size;

    for (size_t i = 0; i < length; i += inc)
    {
        Batch in = Batch::load_aligned(input + i);
        in = xsimd::sin(in);
        in.store_aligned(output + i);
    }
}

void vectorSineScalar(const float* input, float* output, size_t length)
{
    for (size_t i = 0; i < length; ++i)
        output[i] = std::sin(input[i]);
}