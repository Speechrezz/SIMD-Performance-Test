#pragma once

#include "Register.hpp"

#ifdef SSIMD_AVX
#include <cmath>

namespace ssimd
{

template<>
struct Register<float, avx>
{
	__m256 data;

	static inline constexpr size_t size() { return 8; }
	static inline constexpr size_t alignment() { return 32; }

	static inline Register<float, avx> loadAligned(const float* memory)
	{
		return { _mm256_load_ps(memory) };
	}

	inline void storeAligned(float* memory) const
	{
		_mm256_store_ps(memory, data);
	}

	RegisterOverloadsDeclarations(float, avx)
};


// ---Arithmetic---

inline Register<float, avx> add(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_add_ps(reg1.data, reg2.data) };
}

inline Register<float, avx> sub(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_sub_ps(reg1.data, reg2.data) };
}

inline Register<float, avx> mul(const Register<float, avx>& reg1, const Register<float, avx>& reg2)
{
	return { _mm256_mul_ps(reg1.data, reg2.data) };
}


// ---Trig---

#ifdef SSIMD_MSVC // Only available in the MSVC compiler
inline Register<float, avx> sin(const Register<float, avx>& reg)
{
	return { _mm256_sin_ps(reg.data) };
}
#else
inline Register<float, avx> sin(const Register<float, avx>& reg)
{
	return generic::sin(reg);
}
#endif

RegisterOverloadsDefinitions(float, avx)

} // namespace ssimd

#endif