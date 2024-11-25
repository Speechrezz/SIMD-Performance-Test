#pragma once

#include <string>
#include <map>
#include "../Core/Config.hpp"
#include "../Generic/GenericTrig.hpp"

namespace ssimd
{

enum ArchType
{
	fallback, sse, avx, neon, wasm
};

std::map<ArchType, std::string> archToString
{
	{ fallback, "Fallback" },
	{ sse, "SSE" },
	{ avx, "AVX" },
	{ neon, "NEON" },
	{ wasm, "WASM" }
};

template<typename DataType, ArchType archType>
struct Register
{
	static_assert(false, "Arch type not supported");
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

template<typename DataType, ArchType archType>
struct RegisterOverloads
{
private:
	using Derived = Register<DataType, archType>;

public: // Binary
	friend SSIMD_INLINE Derived operator+(Derived const& self, Derived const& other) noexcept
	{
		return add(self, other);
	}

	friend SSIMD_INLINE Derived operator-(Derived const& self, Derived const& other) noexcept
	{
		return sub(self, other);
	}

	friend SSIMD_INLINE Derived operator*(Derived const& self, Derived const& other) noexcept
	{
		return mul(self, other);
	}

	friend SSIMD_INLINE Derived operator/(Derived const& self, Derived const& other) noexcept
	{
		return div(self, other);
	}

public:	// Unary
	friend SSIMD_INLINE Derived operator-(Derived const& self) noexcept
	{
		return neg(self);
	}
};

} // namespace ssimd