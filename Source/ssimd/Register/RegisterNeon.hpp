#pragma once

#include "Register.hpp"

#ifdef SSIMD_NEON
#include <cmath>

namespace ssimd
{

template<>
struct Register<float, neon>
{
	float32x4_t data;

	static inline constexpr size_t size() { return 4; }
	static inline constexpr size_t alignment() { return 16; }

	static inline Register<float, neon> loadAligned(const float* memory)
	{
		return { vld1q_f32(memory) };
	}

	inline void storeAligned(float* memory) const
	{
		vst1q_f32(memory, data);
	}

	RegisterOverloadsDeclarations(float, neon)
};


// ---Arithmetic---

inline Register<float, neon> add(const Register<float, neon>& reg1, const Register<float, neon>& reg2)
{
	return { vaddq_f32(reg1.data, reg2.data) };
}

inline Register<float, neon> sub(const Register<float, neon>& reg1, const Register<float, neon>& reg2)
{
	return { vsubq_f32(reg1.data, reg2.data) };
}

inline Register<float, neon> mul(const Register<float, neon>& reg1, const Register<float, neon>& reg2)
{
	return { vmulq_f32(reg1.data, reg2.data) };
}


// ---Trig---

inline Register<float, neon> sin(const Register<float, neon>& reg)
{
	return generic::sin(reg);
}

RegisterOverloadsDefinitions(float, neon)

} // namespace ssimd

#endif