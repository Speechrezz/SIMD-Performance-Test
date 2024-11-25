#pragma once

#include "Testing.hpp"

namespace ssimd::test
{
	
template<ArchType archType>
bool testFloatLoading()
{
	using Register = Register<float, archType>;

	constexpr auto align = Register::alignment();
	constexpr auto size = Register::size();

	alignas(align) float input[size];
	std::vector<float> desired(size);

	fillArray(input, size);
	fillArray(desired.data(), size);

	auto reg = Register::loadAligned(input);
	EXPECT_EQ_REG(desired, reg, "loadAligned");

	reg = Register::loadUnaligned(input);
	EXPECT_EQ_REG(desired, reg, "loadUnaligned");

	reg = Register::broadcast(2.f);
	std::vector<float> desiredBroadcast(size, 2.f);
	EXPECT_EQ_REG(desiredBroadcast, reg, "broadcast");

	return true;
}

template<ArchType archType>
bool testFloatArithmetic()
{
	using Register = Register<float, archType>;

	constexpr auto align = Register::alignment();
	constexpr auto size = Register::size();

	alignas(align) float input1[size];
	alignas(align) float input2[size];
	std::vector<float> desired(size);

	fillArray(input1, size);
	fillArray(input2, size);
	fillArray(desired.data(), size);

	auto reg1 = Register::loadAligned(input1);
	auto reg2 = Register::loadAligned(input1);

	// Vector-scalar arithmetic

	for (size_t i = 0; i < size; ++i)
		desired[i] = input1[i] + 1.f;
	EXPECT_EQ_REG(desired, reg1 + 1.f, "vector-scalar add");

	for (size_t i = 0; i < size; ++i)
		desired[i] = input1[i] - 1.f;
	EXPECT_EQ_REG(desired, reg1 - 1.f, "vector-scalar sub");

	for (size_t i = 0; i < size; ++i)
		desired[i] = input1[i] * 2.f;
	EXPECT_EQ_REG(desired, reg1 * 2.f, "vector-scalar mul");

	for (size_t i = 0; i < size; ++i)
		desired[i] = input1[i] / 2.f;
	EXPECT_EQ_REG(desired, reg1 / 2.f, "vector-scalar div");

	// Vector-vector arithmetic

	for (size_t i = 0; i < size; ++i)
		desired[i] = input1[i] + input2[i];
	EXPECT_EQ_REG(desired, reg1 + reg2, "vector-vector add");

	for (size_t i = 0; i < size; ++i)
		desired[i] = input1[i] - input2[i];
	EXPECT_EQ_REG(desired, reg1 - reg2, "vector-vector sub");

	for (size_t i = 0; i < size; ++i)
		desired[i] = input1[i] * input2[i];
	EXPECT_EQ_REG(desired, reg1 * reg2, "vector-vector mul");

	for (size_t i = 0; i < size; ++i)
		desired[i] = input1[i] / (input2[i] + 1.f);
	EXPECT_EQ_REG(desired, reg1 / (reg2 + 1.f), "vector-vector div");

	return true;
}

template<ArchType archType>
bool testFloatUnary()
{
	using Register = Register<float, archType>;

	constexpr auto align = Register::alignment();
	constexpr auto size = Register::size();

	alignas(align) float input[size];
	std::vector<float> desired(size);

	fillArray(input, size);
	fillArray(desired.data(), size);

	auto reg = Register::loadAligned(input);

	for (size_t i = 0; i < size; ++i)
		desired[i] = -input[i];
	EXPECT_EQ_REG(desired, neg(reg), "neg");

	return true;
}

template<ArchType archType>
bool testFloatRounding()
{
	using Register = Register<float, archType>;

	constexpr auto align = Register::alignment();
	constexpr auto size = Register::size();

	alignas(align) float input[size];
	std::vector<float> desired(size);

	fillArray(input, size);
	fillArray(desired.data(), size);

	auto reg = Register::loadAligned(input);

	reg = 3.6f * (reg - 2.f);
	for (size_t i = 0; i < size; ++i)
		input[i] = 3.6f * (input[i] - 2.f);

	for (size_t i = 0; i < size; ++i)
		desired[i] = std::round(input[i]);
	EXPECT_EQ_REG(desired, round(reg), "round");

	for (size_t i = 0; i < size; ++i)
		desired[i] = std::ceil(input[i]);
	EXPECT_EQ_REG(desired, ceil(reg), "ceil");

	for (size_t i = 0; i < size; ++i)
		desired[i] = std::floor(input[i]);
	EXPECT_EQ_REG(desired, floor(reg), "floor");

	for (size_t i = 0; i < size; ++i)
		desired[i] = std::trunc(input[i]);
	EXPECT_EQ_REG(desired, trunc(reg), "trunc");

	return true;
}

} // namespace ssimd::testing