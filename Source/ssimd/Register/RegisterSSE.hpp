#pragma once

#include "Register.hpp"

#ifdef SSIMD_SSE
#include <cmath>

namespace ssimd
{

template<>
struct Register<float, sse>
{
	__m128 data;

	static inline constexpr size_t size() { return 4; }
	static inline constexpr size_t alignment() { return 16; }

	static inline Register<float, sse> loadAligned(const float* memory)
	{
		return { _mm_load_ps(memory) };
	}

	inline void storeAligned(float* memory) const
	{
		_mm_store_ps(memory, data);
	}

	RegisterOverloadsDeclarations(float, sse)
};


// ---Arithmetic---

inline Register<float, sse> add(const Register<float, sse>& reg1, const Register<float, sse>& reg2)
{
	return { _mm_add_ps(reg1.data, reg2.data) };
}

inline Register<float, sse> sub(const Register<float, sse>& reg1, const Register<float, sse>& reg2)
{
	return { _mm_sub_ps(reg1.data, reg2.data) };
}

inline Register<float, sse> mul(const Register<float, sse>& reg1, const Register<float, sse>& reg2)
{
	return { _mm_mul_ps(reg1.data, reg2.data) };
}


// ---Trig---

#ifdef SSIMD_MSVC
inline Register<float, sse> sin(const Register<float, sse>& reg)
{
	return { _mm_sin_ps(reg.data) };
}
#else
inline Register<float, sse> sin(const Register<float, sse>& reg)
{
	return generic::sin(reg);
}
#endif

RegisterOverloadsDefinitions(float, sse)

} // namespace ssimd

#endif