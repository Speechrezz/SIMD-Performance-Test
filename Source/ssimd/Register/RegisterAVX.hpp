#pragma once

#include "Register.hpp"

#ifdef SSIMD_AVX
#include <cmath>

namespace ssimd
{

template<>
struct Register<float, avx> : public RegisterOverloads<float, avx>
{
	__m256 data;

	Register() = default;
	SSIMD_INLINE Register(const Register<float, avx>& other) noexcept : data(other.data) {}
	SSIMD_INLINE Register(const __m256& newData) noexcept : data(newData) {}
	SSIMD_INLINE Register(float scalar) noexcept : Register(broadcast(scalar)) {}

	static SSIMD_INLINE constexpr size_t size() { return 8; }
	static SSIMD_INLINE constexpr size_t alignment() { return 32; }

	static SSIMD_INLINE Register<float, avx> broadcast(float scalar)
	{
		return { _mm256_set1_ps(scalar) };
	}

	static SSIMD_INLINE Register<float, avx> loadUnaligned(const float* memory)
	{
		return { _mm256_loadu_ps(memory) };
	}
	static SSIMD_INLINE Register<float, avx> loadAligned(const float* memory)
	{
		return { _mm256_load_ps(memory) };
	}

	SSIMD_INLINE void storeUnaligned(float* memory) const
	{
		_mm256_storeu_ps(memory, data);
	}
	SSIMD_INLINE void storeAligned(float* memory) const
	{
		_mm256_store_ps(memory, data);
	}
};


// ---Arithmetic---

SSIMD_INLINE Register<float, avx> add(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_add_ps(reg1.data, reg2.data) };
}

SSIMD_INLINE Register<float, avx> sub(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_sub_ps(reg1.data, reg2.data) };
}

SSIMD_INLINE Register<float, avx> mul(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_mul_ps(reg1.data, reg2.data) };
}

SSIMD_INLINE Register<float, avx> div(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_div_ps(reg1.data, reg2.data) };
}


// ---Rounding---

SSIMD_INLINE Register<float, avx> round(const Register<float, avx>& reg)
{
	return { _mm256_round_ps(reg.data, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
}

SSIMD_INLINE Register<float, avx> ceil(const Register<float, avx>& reg)
{
	return { _mm256_round_ps(reg.data, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC) };
}

SSIMD_INLINE Register<float, avx> floor(const Register<float, avx>& reg)
{
	return { _mm256_round_ps(reg.data, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC) };
}

SSIMD_INLINE Register<float, avx> trunc(const Register<float, avx>& reg)
{
	return { _mm256_round_ps(reg.data, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
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