#pragma once

#include "Register.hpp"

namespace ssimd
{

template<>
struct Register<float, fallback>
{
	float data;

	static inline constexpr size_t size() { return 1; }
	static inline constexpr size_t alignment() { return 4; }

	static inline Register<float, fallback> loadAligned(const float* memory)
	{
		return { *memory };
	}

	inline void storeAligned(float* memory) const
	{
		*memory = data;
	}

	RegisterOverloadsDeclarations(float, fallback)
};


// ---Arithmetic---

inline Register<float, fallback> add(const Register<float, fallback>& reg1, const Register<float, fallback>& reg2)
{
	return { reg1.data + reg2.data };
}

inline Register<float, fallback> sub(const Register<float, fallback>& reg1, const Register<float, fallback>& reg2)
{
	return { reg1.data - reg2.data };
}

inline Register<float, fallback> mul(const Register<float, fallback>& reg1, const Register<float, fallback>& reg2)
{
	return { reg1.data * reg2.data };
}


// ---Trig---

inline Register<float, fallback> sin(const Register<float, fallback>& reg)
{
	return { std::sin(reg.data) };
}

RegisterOverloadsDefinitions(float, fallback)

} // namespace ssimd