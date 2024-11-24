#pragma once

#include "../Core/Config.hpp"

namespace ssimd
{

enum RegisterType
{
	fallback, sse, avx, neon, wasm
};

template<RegisterType registerType>
struct Register
{
	static_assert(false, "Register type not supported");
};

#if defined(SSIMD_AVX)
  constexpr RegisterType bestArch = RegisterType::avx;
#elif defined(SSIMD_SSE)
  constexpr RegisterType bestArch = RegisterType::sse;
#elif defined(SSIMD_NEON)
  constexpr RegisterType bestArch = RegisterType::neon;
#elif defined(SSIMD_WASM)
  constexpr RegisterType bestArch = RegisterType::wasm;
#else
  constexpr RegisterType bestArch = RegisterType::fallback;
#endif

} // namespace ssimd