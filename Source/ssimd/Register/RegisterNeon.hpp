#pragma once

#include "Register.hpp"

#ifdef SSIMD_NEON
#include <cmath>

namespace ssimd
{

template<>
struct Register<float, neon> : public RegisterOverloads<Register<float, neon>>
{
	float32x4_t data;

	Register() = default;
	SSIMD_INLINE Register(const float32x4_t& newData) : data(newData) {}

	static SSIMD_INLINE constexpr size_t size() { return 4; }
	static SSIMD_INLINE constexpr size_t alignment() { return 16; }

	static SSIMD_INLINE Register<float, neon> loadAligned(const float* memory)
	{
		return { vld1q_f32(memory) };
	}

	SSIMD_INLINE void storeAligned(float* memory) const
	{
		vst1q_f32(memory, data);
	}
};


// ---Arithmetic---

SSIMD_INLINE Register<float, neon> add(const Register<float, neon>& reg1, const Register<float, neon>& reg2)
{
	return { vaddq_f32(reg1.data, reg2.data) };
}

SSIMD_INLINE Register<float, neon> sub(const Register<float, neon>& reg1, const Register<float, neon>& reg2)
{
	return { vsubq_f32(reg1.data, reg2.data) };
}

SSIMD_INLINE Register<float, neon> mul(const Register<float, neon>& reg1, const Register<float, neon>& reg2)
{
	return { vmulq_f32(reg1.data, reg2.data) };
}


// ---Trig---

SSIMD_INLINE Register<float, neon> sin(const Register<float, neon>& reg)
{
	return generic::sin(reg);
}

} // namespace ssimd

#endif