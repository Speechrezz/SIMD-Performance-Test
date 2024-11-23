#include <iostream>
#include <vector>

#include "VectorSineTest.h"
#include "Timer.h"

constexpr size_t vectorLength = 1024;
constexpr size_t numIterations = 2000000;

void benchmarkVectorSine()
{
    alignas(32) float input[vectorLength];
    alignas(32) float output[vectorLength];
    fillArray(input, vectorLength);

    Timer timer;
    std::cout << "\n---Sine---\n";

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) 
    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineAvx(input, output, vectorLength);
    std::cout << "AVX Intrinsics: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";
#elif defined(__APPLE__)
    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineAccelerate(input, output, vectorLength);
    std::cout << "Accelerate: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";
#endif

    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineXsimd(input, output, vectorLength);
    std::cout << "XSIMD: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";

    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineEve(input, output, vectorLength);
    std::cout << "EVE: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";

    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineScalar(input, output, vectorLength);
    std::cout << "Scalar: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";
}

void benchmarkVectorAdd()
{
    alignas(32) float input1[vectorLength];
    alignas(32) float input2[vectorLength];
    alignas(32) float output[vectorLength];
    fillArray(input1, vectorLength);
    fillArray(input2, vectorLength);

    Timer timer;
    std::cout << "\n---Add---\n";

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) 
    timer.start();
    for (size_t i = 0; i < numIterations * 10; ++i)
        vectorAddAvx(input1, input2, output, vectorLength);
    std::cout << "AVX Intrinsics: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";
#elif defined(__APPLE__)
    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorAddAccelerate(input1, input2, output, vectorLength);
    std::cout << "Accelerate: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";
#endif

    timer.start();
    for (size_t i = 0; i < numIterations * 10; ++i)
        vectorAddXsimd(input1, input2, output, vectorLength);
    std::cout << "XSIMD: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";

    timer.start();
    for (size_t i = 0; i < numIterations * 10; ++i)
        vectorAddEve(input1, input2, output, vectorLength);
    std::cout << "EVE: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";

    timer.start();
    for (size_t i = 0; i < numIterations * 10; ++i)
        vectorAddScalar(input1, input2, output, vectorLength);
    std::cout << "Scalar: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";
}

int main()
{
    benchmarkVectorAdd();
    benchmarkVectorSine();

    return 0;
}