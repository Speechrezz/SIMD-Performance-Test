#pragma once

#include "Register.hpp"

namespace ssimd
{

template<>
struct Register<fallback>
{
	float data;

	static inline constexpr size_t size() { return 1; }
	static inline constexpr size_t alignment() { return 4; }

	static inline Register<fallback> loadAligned(const float* memory)
	{
		return { *memory };
	}

	inline void storeAligned(float* memory) const
	{
		*memory = data;
	}

	RegisterOverloadsDeclarations(Register<fallback>)
};


// ---Arithmetic---

inline Register<fallback> add(const Register<fallback>& reg1, const Register<fallback>& reg2)
{
	return { reg1.data + reg2.data };
}

inline Register<fallback> sub(const Register<fallback>& reg1, const Register<fallback>& reg2)
{
	return { reg1.data - reg2.data };
}

inline Register<fallback> mul(const Register<fallback>& reg1, const Register<fallback>& reg2)
{
	return { reg1.data * reg2.data };
}


// ---Trig---

inline Register<fallback> sin(const Register<fallback>& reg)
{
	return { std::sin(reg.data) };
}

RegisterOverloadsDefinitions(Register<fallback>)

} // namespace ssimd