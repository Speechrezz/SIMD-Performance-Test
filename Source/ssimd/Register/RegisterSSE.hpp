#pragma once

#include "Register.hpp"

#ifdef SSIMD_SSE
#include <cmath>

namespace ssimd
{

template<>
struct Register<sse>
{
	__m128 data;

	static inline constexpr size_t size() { return 4; }
	static inline constexpr size_t alignment() { return 16; }

	static inline Register<sse> loadAligned(const float* memory)
	{
		return { _mm_load_ps(memory) };
	}

	inline void storeAligned(float* memory) const
	{
		_mm_store_ps(memory, data);
	}
};

inline Register<sse> add(const Register<sse>& reg1, const Register<sse>& reg2)
{
	return { _mm_add_ps(reg1.data, reg2.data) };
}

#ifdef SSIMD_MSVC
inline Register<sse> sin(const Register<sse>& reg)
{
	return { _mm_sin_ps(reg.data) };
}
#else
inline Register<sse> sin(const Register<sse>& reg)
{
	return generic::sin(reg);
}
#endif

} // namespace ssimd

#endif