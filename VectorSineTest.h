//
// Created by Mark Muranov on 11/22/24.
//

#pragma once

#include "xsimd/xsimd.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>

void fillArray(float* array, size_t length)
{
    for (size_t i = 0; i < length; ++i)
        array[i] = static_cast<float>(i);
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <immintrin.h>
void vectorAddAvx(const float* input1, const float* input2, float* output, size_t length)
{
    for (size_t i = 0; i < length; i += 8)
    {
        __m256 in1 = _mm256_load_ps(input1 + i);
        __m256 in2 = _mm256_load_ps(input2 + i);
        _mm256_store_ps(output + i, _mm256_add_ps(in1, in2));
    }
}


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

void vectorAddAccelerate(const float* input1, const float* input2, float* output, size_t length)
{
    vDSP_vadd(input1, 1, input2, 1, output, 1, length);
}

void vectorSineAccelerate(const float* input, float* output, size_t length)
{
    const int lengthInt = static_cast<int>(length);
    vvsinf(output, input, &lengthInt);
}
#endif

void vectorAddXsimd(const float* input1, const float* input2, float* output, size_t length)
{
    using Batch = xsimd::batch<float, xsimd::best_arch>;
    const size_t inc = Batch::size;

    for (size_t i = 0; i < length; i += inc)
    {
        Batch in1 = Batch::load_aligned(input1 + i);
        Batch in2 = Batch::load_aligned(input2 + i);
        Batch sum = in1 + in2;
        sum.store_aligned(output + i);
    }
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

//void vectorAddEve(const float* input1, const float* input2, float* output, size_t length)
//{
//    // Process in chunks of the SIMD wide size
//    auto wide_size = eve::wide<float>::size();
//    for (size_t i = 0; i < length; i += wide_size) {
//        // Load SIMD chunks
//        auto va = eve::load(input1 + i, eve::lane<wide_size>);
//        auto vb = eve::load(input2 + i, eve::lane<wide_size>);
//
//        // Perform element-wise addition
//        auto vr = va + vb;
//
//        // Store the result back
//        eve::store(vr, output + i);
//    }
//}

void vectorSineEve(const float* input, float* output, size_t length) {
    size_t simd_size = eve::wide<float>::size();
    for (size_t i = 0; i < length; i += simd_size) 
    {
        eve::wide<float> in = eve::load(&input[i]);
        eve::wide<float> out = eve::sin(in);
        eve::store(out, &output[i]);
    }
}

void vectorAddScalar(const float* input1, const float* input2, float* output, size_t length)
{
    for (size_t i = 0; i < length; ++i)
        output[i] = input1[i] + input2[i];
}

void vectorSineScalar(const float* input, float* output, size_t length)
{
    for (size_t i = 0; i < length; ++i)
        output[i] = std::sin(input[i]);
}