#pragma once

#include "Config.hpp"
#include <cmath>

namespace ssimd::generic
{

// ---Fused---

template<typename Register>
SSIMD_INLINE Register fma(const Register& a, const Register& b, const Register& c)
{
	return { a * b + c };
}

template<typename Register>
SSIMD_INLINE Register fms(const Register& a, const Register& b, const Register& c)
{
	return { a * b - c };
}

template<typename Register>
SSIMD_INLINE Register fnma(const Register& a, const Register& b, const Register& c)
{
	return { -a * b + c };
}

template<typename Register>
SSIMD_INLINE Register fnms(const Register& a, const Register& b, const Register& c)
{
	return { -a * b - c };
}


// ---Trig---

template<typename Register>
SSIMD_INLINE Register sin(const Register& reg)
{
	// TODO: Come up with a better generic implementation
	alignas(Register::size()) float arr[Register::size()];
	reg.storeAligned(arr);

	for (float& v : arr)
		v = std::sin(v);

	return Register::loadAligned(arr);
}

} // namespace ssimd::generic
