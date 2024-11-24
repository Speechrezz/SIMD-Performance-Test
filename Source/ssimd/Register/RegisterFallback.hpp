#pragma once

#include "Register.hpp"

namespace ssimd
{

template<>
struct Register<float, fallback> : public RegisterOverloads<Register<float, fallback>>
{
	float data;

	Register() = default;
	SSIMD_INLINE Register(const float& newData) : data(newData) {}

	static SSIMD_INLINE constexpr size_t size() { return 1; }
	static SSIMD_INLINE constexpr size_t alignment() { return 4; }

	static SSIMD_INLINE Register<float, fallback> loadAligned(const float* memory)
	{
		return { *memory };
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


// ---Trig---

SSIMD_INLINE Register<float, fallback> sin(const Register<float, fallback>& reg)
{
	return { std::sin(reg.data) };
}

} // namespace ssimd