#pragma once

#include "Register.hpp"

#ifdef SSIMD_AVX
#include <cmath>

namespace ssimd
{

template<>
struct Register<avx>
{
	__m256 data;

	static inline constexpr size_t size() { return 8; }
	static inline constexpr size_t alignment() { return 32; }

	static inline Register<avx> loadAligned(const float* memory)
	{
		return { _mm256_load_ps(memory) };
	}

	inline void storeAligned(float* memory) const
	{
		_mm256_store_ps(memory, data);
	}

	RegisterOverloadsDeclarations(Register<avx>)
};

inline Register<avx> add(const Register<avx>& reg1, const Register<avx>& reg2)
{
	return { _mm256_add_ps(reg1.data, reg2.data) };
}

#ifdef SSIMD_MSVC // Only available in the MSVC compiler
inline Register<avx> sin(const Register<avx>& reg)
{
	return { _mm256_sin_ps(reg.data) };
}
#else
inline Register<avx> sin(const Register<avx>& reg)
{
	return generic::sin(reg);
}
#endif

RegisterOverloadsDefinitions(Register<avx>)

} // namespace ssimd

#endif