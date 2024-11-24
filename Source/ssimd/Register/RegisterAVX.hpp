#pragma once

#include "Register.hpp"

#ifdef SSIMD_AVX
#include <cmath>

namespace ssimd
{

template<>
struct Register<float, avx> : public RegisterOverloads<Register<float, avx>>
{
	__m256 data;

	Register() = default;
	SSIMD_INLINE Register(const __m256& newData) : data(newData) {}

	static SSIMD_INLINE constexpr size_t size() { return 8; }
	static SSIMD_INLINE constexpr size_t alignment() { return 32; }

	static SSIMD_INLINE Register<float, avx> loadAligned(const float* memory)
	{
		return { _mm256_load_ps(memory) };
	}

	SSIMD_INLINE void storeAligned(float* memory) const
	{
		_mm256_store_ps(memory, data);
	}
};


// ---Arithmetic---

static SSIMD_INLINE Register<float, avx> add(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_add_ps(reg1.data, reg2.data) };
}

static SSIMD_INLINE Register<float, avx> sub(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_sub_ps(reg1.data, reg2.data) };
}

static SSIMD_INLINE Register<float, avx> mul(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_mul_ps(reg1.data, reg2.data) };
}

static SSIMD_INLINE Register<float, avx> div(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_div_ps(reg1.data, reg2.data) };
}


// ---Trig---

SSIMD_INLINE Register<float, avx> sin(const Register<float, avx>& reg)
{
#ifdef SSIMD_MSVC
	return { _mm256_sin_ps(reg.data) };
#else
	return generic::sin(reg);
#endif
}

} // namespace ssimd

#endif