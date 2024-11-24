#pragma once

#include "../Core/Config.hpp"
#include "../Generic/GenericTrig.hpp"

namespace ssimd
{

enum ArchType
{
	fallback, sse, avx, neon, wasm
};

template<typename dataType,ArchType registerType>
struct Register
{
	static_assert(false, "Register type not supported");
};

#if defined(SSIMD_AVX)
  constexpr ArchType bestArch = ArchType::avx;
#elif defined(SSIMD_SSE)
  constexpr ArchType bestArch = ArchType::sse;
#elif defined(SSIMD_NEON)
  constexpr ArchType bestArch = ArchType::neon;
#elif defined(SSIMD_WASM)
  constexpr ArchType bestArch = ArchType::wasm;
#else
  constexpr ArchType bestArch = ArchType::fallback;
#endif

template<class Derived>
struct RegisterOverloads
{
	SSIMD_INLINE Derived operator+(const Derived& other) const
	{
		return add(*static_cast<const Derived*>(this), other);
	}

	SSIMD_INLINE Derived operator-(const Derived& other) const
	{
		return sub(*static_cast<const Derived*>(this), other);
	}

	SSIMD_INLINE Derived operator*(const Derived& other) const
	{
		return mul(*static_cast<const Derived*>(this), other);
	}

	SSIMD_INLINE Derived operator/(const Derived& other) const
	{
		return div(*static_cast<const Derived*>(this), other);
	}
};

} // namespace ssimd