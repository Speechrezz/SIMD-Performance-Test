#pragma once

#include "Register.hpp"

#ifdef SSIMD_NEON
#include <cmath>

namespace ssimd
{

template<>
struct Register<neon>
{
	float32x4_t data;

	static inline constexpr size_t size() { return 4; }
	static inline constexpr size_t alignment() { return 16; }

	static inline Register<neon> loadAligned(const float* memory)
	{
		return { vld1q_f32(memory) };
	}

	inline void storeAligned(float* memory) const
	{
		vst1q_f32(memory, data);
	}

	RegisterOverloadsDeclarations(Register<neon>)
};

inline Register<neon> add(const Register<neon>& reg1, const Register<neon>& reg2)
{
	return { vaddq_f32(reg1.data, reg2.data) };
}

inline Register<neon> sin(const Register<neon>& reg)
{
	return generic::sin(reg);
}

RegisterOverloadsDefinitions(Register<neon>)

} // namespace ssimd

#endif