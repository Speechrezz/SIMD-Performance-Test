#include <iostream>
#include <vector>

#include "VectorSineTest.h"
#include "Timer.h"

constexpr size_t vectorLength = 1024;
constexpr size_t numIterations = 1000000;

int main()
{
    alignas(32) float input[vectorLength];
    alignas(32) float output[vectorLength];
    fillArray(input, vectorLength);

    Timer timer;

#if defined(__APPLE__)
    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineAccelerate(input, output, vectorLength);
    std::cout << "Accelerate: " << timer.stop().elapsed() << " (sec)\n";
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) 
    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineAvx(input, output, vectorLength);
    std::cout << "AVX Intrinsics: " << timer.stop().elapsed() << " (sec)\n";
#endif

    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineXsimd(input, output, vectorLength);
    std::cout << "XSIMD: " << timer.stop().elapsed() << " (sec)\n";

    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineScalar(input, output, vectorLength);
    std::cout << "Scalar: " << timer.stop().elapsed() << " (sec)\n";

    return 0;
}