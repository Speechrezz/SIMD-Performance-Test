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

    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineAccelerate(input, output, vectorLength);
    const double accelerateTime = timer.stop().elapsed();

    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineXsimd(input, output, vectorLength);
    const double xsimdTime = timer.stop().elapsed();

    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineScalar(input, output, vectorLength);
    const double scalarTime = timer.stop().elapsed();

    std::cout << "Accelerate: " << accelerateTime << " (sec)\n";
    std::cout << "XSIMD: " << xsimdTime << " (sec)\n";
    std::cout << "Scalar: " << scalarTime << " (sec)\n";

    return 0;
}