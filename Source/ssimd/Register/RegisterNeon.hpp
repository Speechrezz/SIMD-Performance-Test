#pragma once

#include "Register.hpp"

#ifdef SSIMD_NEON
#include <cmath>

namespace ssimd
{

template<>
struct Register<float, neon> : public RegisterOverloads<float, neon>
{
	float32x4_t data;

	Register() = default;
	SSIMD_INLINE Register(const Register<float, neon>& other) noexcept : data(other.data) {}
	SSIMD_INLINE Register(const float32x4_t& newData) : data(newData) {}
    SSIMD_INLINE Register(float scalar) noexcept : Register(broadcast(scalar)) {}

	static SSIMD_INLINE constexpr size_t size() { return 4; }
	static SSIMD_INLINE constexpr size_t alignment() { return 16; }

	static SSIMD_INLINE Register<float, neon> broadcast(float scalar)
	{
		return { vdupq_n_f32(scalar) };
	}

	static SSIMD_INLINE Register<float, neon> loadUnaligned(const float* memory)
	{
		return { vld1q_f32(memory) };
	}
	static SSIMD_INLINE Register<float, neon> loadAligned(const float* memory)
	{
		return { vld1q_f32(memory) };
	}

	SSIMD_INLINE void storeUnaligned(float* memory) const
	{
		vst1q_f32(memory, data);
	}
	SSIMD_INLINE void storeAligned(float* memory) const
	{
		vst1q_f32(memory, data);
	}
};

template <ArchType Arch>
using enable_if_neon = typename std::enable_if<Arch == neon, Register<float, Arch>>::type;

// ---Arithmetic---

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> add(const Register<float, Arch>& reg1, const Register<float, Arch>& reg2)
{
	return { vaddq_f32(reg1.data, reg2.data) };
}

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> sub(const Register<float, Arch>& reg1, const Register<float, Arch>& reg2)
{
	return { vsubq_f32(reg1.data, reg2.data) };
}

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> mul(const Register<float, Arch>& reg1, const Register<float, Arch>& reg2)
{
	return { vmulq_f32(reg1.data, reg2.data) };
}

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> div(const Register<float, Arch>& reg1, const Register<float, Arch>& reg2)
{
	return { vdivq_f32(reg1.data, reg2.data) };
}


// ---Unary---

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> neg(const Register<float, Arch>& reg)
{
	return { vnegq_f32(reg.data) };
}


// ---Fused---

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> fma(const Register<float, Arch>& a, const Register<float, Arch>& b, const Register<float, Arch>& c)
{
    return { vfmaq_f32(c.data, a.data, b.data) };
}

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> fms(const Register<float, Arch>& a, const Register<float, Arch>& b, const Register<float, Arch>& c)
{
    return fma(a, b, -c);
}

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> fnma(const Register<float, Arch>& a, const Register<float, Arch>& b, const Register<float, Arch>& c)
{
    return { vfmsq_f32(c.data, a.data, b.data) };
}

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> fnms(const Register<float, Arch>& a, const Register<float, Arch>& b, const Register<float, Arch>& c)
{
    return -fma(a, b, c);
}


// ---Rounding---

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> round(const Register<float, Arch>& reg)
{
	return { vrndnq_f32(reg.data) };
}

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> ceil(const Register<float, Arch>& reg)
{
	return { vrndpq_f32(reg.data) };
}

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> floor(const Register<float, Arch>& reg)
{
	return { vrndmq_f32(reg.data) };
}

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> trunc(const Register<float, Arch>& reg)
{
	return { vrndq_f32(reg.data) };
}


// ---Trig---

template <ArchType Arch>
SSIMD_INLINE enable_if_neon<Arch> sin(const Register<float, Arch>& reg)
{
	return generic::sin(reg);
}

} // namespace ssimd

#endif