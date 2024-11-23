//
// Created by Mark Muranov on 11/22/24.
//

#pragma once

#include "Accelerate/Accelerate.h"
#include "xsimd/xsimd.hpp"

void fillArray(float* array, size_t length)
{
    for (size_t i = 0; i < length; ++i)
        array[i] = static_cast<float>(i);
}

void vectorSineAccelerate(const float* input, float* output, size_t length)
{
    const int lengthInt = static_cast<int>(length);
    vvsinf(output, input, &lengthInt);
}

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