#pragma once

#include "Register.hpp"

namespace ssimd
{

template<>
struct Register<float, fallback> : public RegisterOverloads<float, fallback>
{
	float data;

	Register() = default;
	SSIMD_INLINE Register(const Register<float, fallback>& other) noexcept : data(other.data) {}
	SSIMD_INLINE Register(float newData) : data(newData) {}

	static SSIMD_INLINE constexpr size_t size() { return 1; }
	static SSIMD_INLINE constexpr size_t alignment() { return 4; }

	static SSIMD_INLINE Register<float, fallback> broadcast(float scalar)
	{
		return { scalar };
	}

	static SSIMD_INLINE Register<float, fallback> loadUnaligned(const float* memory)
	{
		return { *memory };
	}
	static SSIMD_INLINE Register<float, fallback> loadAligned(const float* memory)
	{
		return { *memory };
	}

	SSIMD_INLINE void storeUnaligned(float* memory) const
	{
		*memory = data;
	}
	SSIMD_INLINE void storeAligned(float* memory) const
	{
		*memory = data;
	}
};


// ---Arithmetic---

SSIMD_INLINE Register<float, fallback> add(const Register<float, fallback>& reg1, const Register<float, fallback>& reg2)
{
	return { reg1.data + reg2.data };
}

SSIMD_INLINE Register<float, fallback> sub(const Register<float, fallback>& reg1, const Register<float, fallback>& reg2)
{
	return { reg1.data - reg2.data };
}

SSIMD_INLINE Register<float, fallback> mul(const Register<float, fallback>& reg1, const Register<float, fallback>& reg2)
{
	return { reg1.data * reg2.data };
}

SSIMD_INLINE Register<float, fallback> div(const Register<float, fallback>& reg1, const Register<float, fallback>& reg2)
{
	return { reg1.data / reg2.data };
}


// ---Rounding---

SSIMD_INLINE Register<float, fallback> round(const Register<float, fallback>& reg)
{
	return std::round(reg.data);
}

SSIMD_INLINE Register<float, fallback> ceil(const Register<float, fallback>& reg)
{
	return std::ceil(reg.data);
}

SSIMD_INLINE Register<float, fallback> floor(const Register<float, fallback>& reg)
{
	return std::floor(reg.data);
}

SSIMD_INLINE Register<float, fallback> trunc(const Register<float, fallback>& reg)
{
	return std::trunc(reg.data);
}


// ---Trig---

SSIMD_INLINE Register<float, fallback> sin(const Register<float, fallback>& reg)
{
	return { std::sin(reg.data) };
}

} // namespace ssimd