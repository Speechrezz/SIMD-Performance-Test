#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

namespace ssimd::test
{

constexpr float pi = 3.14159265358979323846f;

void fillArray(float* array, size_t length)
{
	if (length == 1)
	{
		array[0] = 1;
		return;
	}

	for (size_t i = 0; i < length; ++i)
		array[i] = static_cast<float>(i);
}

template<typename Register>
bool compareRegisterEq(const std::vector<float>& desired, const Register& reg)
{
	float arr[Register::size()];
	reg.storeUnaligned(arr);

	for (size_t i = 0; i < Register::size(); ++i)
		if (desired[i] != arr[i])
			return false;

	return true;
}

template<typename T>
std::string arrayToString(const T* arr, size_t length)
{
	std::stringstream outputStream;
	outputStream << "[";

	for (size_t i = 0; i < length - 1; ++i)
		outputStream << arr[i] << ", ";

	outputStream << arr[length - 1] << "]";
	return outputStream.str();
}

template<typename T>
std::string arrayToString(const std::vector<T>& vec)
{
	return arrayToString(vec.data(), vec.size());
}

template<typename Register>
std::string registerToString(const Register& reg)
{
	alignas(Register::alignment()) float arr[Register::size()];
	reg.storeAligned(arr);

	return arrayToString(arr, Register::size());
}

#define EXPECT_EQ_REG(desired, actual, testName) \
	if (!compareRegisterEq(desired, actual)) \
	{ \
		std::cout << "Test '" << testName << "' FAILED.\n"; \
		std::cout << "  Expected: " << arrayToString(desired) << "\n"; \
		std::cout << "  Got:      " << registerToString(actual) << "\n" << std::endl; \
		return false; \
	}

} // namespace ssimd::test