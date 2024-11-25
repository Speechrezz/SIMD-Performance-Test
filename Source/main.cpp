#include <iostream>
#include <vector>
#include <typeinfo>

#include "VectorSineTest.hpp"
#include "Timer.hpp"
#include "Testing/Testing.hpp"
#include "Testing/TestFloat.hpp"

constexpr size_t vectorLength = 1024;
constexpr size_t numIterations = 2000000;

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
        vectorAddSsimd(input1, input2, output, vectorLength);
    std::cout << "SSIMD: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";

    timer.start();
    for (size_t i = 0; i < numIterations * 10; ++i)
        vectorAddScalar(input1, input2, output, vectorLength);
    std::cout << "Scalar: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";
}

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
        vectorSineSsimd(input, output, vectorLength);
    std::cout << "SSIMD: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";

    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineSsimdArray(input, output, vectorLength);
    std::cout << "SSIMD Array: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";

    timer.start();
    for (size_t i = 0; i < numIterations; ++i)
        vectorSineScalar(input, output, vectorLength);
    std::cout << "Scalar: " << timer.stop().elapsed() << " (sec), output[1]: " << output[1] << "\n";
}

template<class Register>
void printRegister(const Register& reg)
{
    alignas(Register::alignment()) float arr[Register::size()];
    reg.storeAligned(arr);

    std::cout << "[";

    for (size_t i = 0; i < Register::size() - 1; ++i)
        std::cout << arr[i] << ", ";

    std::cout << arr[Register::size() - 1] << "]\n";
}

template<ssimd::ArchType archType>
bool runTests()
{
    bool result = true;

    std::cout << "\n---Testing arch:" << ssimd::archToString[archType] << "---\n";

    result = result && ssimd::test::testFloatLoading<archType>();
    result = result && ssimd::test::testFloatArithmetic<archType>();
    result = result && ssimd::test::testFloatUnary<archType>();
    result = result && ssimd::test::testFloatRounding<archType>();
    
    if (result)
        std::cout << "All tests PASSED.\n";

    return true;
}

void runAllTests()
{
    runTests<ssimd::fallback>();
#ifdef SSIMD_AVX
    runTests<ssimd::avx>();
#endif
#ifdef SSIMD_SSE
    runTests<ssimd::sse>();
#endif
#ifdef SSIMD_NEON
    runTests<ssimd::neon>();
#endif
}

int main()
{
    //benchmarkVectorAdd();
    //benchmarkVectorSine();

    runAllTests();

    return 0;
}