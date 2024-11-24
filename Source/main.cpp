#include <iostream>
#include <vector>

#include "VectorSineTest.h"
#include "Timer.h"

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

template<class Register>
void testSSIMD()
{
    constexpr auto align = Register::alignment();
    constexpr auto size = Register::size();

    alignas(align) float input1[size];
    alignas(align) float input2[size];
    alignas(align) float output[size];
    fillArray(input1, size);
    fillArray(input2, size);

    auto in1 = Register::loadAligned(input1);
    auto in2 = Register::loadAligned(input2);

    std::cout << "in1 + in2 = ";
    printRegister(in1 + in2);

    std::cout << "in1 - in2 = ";
    printRegister(in1 - in2);

    std::cout << "in1 * in2 = ";
    printRegister(in1 * in2);

    std::cout << "sin(in1) = ";
    printRegister(ssimd::sin(in1));
}

int main()
{
    //benchmarkVectorAdd();
    //benchmarkVectorSine();

    std::cout << "\n---Fallback---\n";
    testSSIMD<ssimd::Register<float, ssimd::fallback>>();
#ifdef SSIMD_AVX
    std::cout << "\n---AVX---\n";
    testSSIMD<ssimd::Register<float, ssimd::avx>>();
#endif
#ifdef SSIMD_SSE
    std::cout << "\n---SSE---\n";
    testSSIMD<ssimd::Register<float, ssimd::sse>>();
#endif
#ifdef SSIMD_NEON
    std::cout << "\n---Neon---\n";
    testSSIMD<ssimd::Register<float, ssimd::neon>>();
#endif

    return 0;
}