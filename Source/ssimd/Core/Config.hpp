#pragma once


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) 
  #define SSIMD_WINDOWS 1
#elif defined __APPLE__
  #define SSIMD_APPLE 1
  #include "Accelerate/Accelerate.h"
#else
  #error "System NOT supported"
#endif


#if defined(_MSC_VER)
  #define SSIMD_MSVC
#endif


#if defined(__AVX__) || defined(__AVX2__)
  #define SSIMD_AVX 1
  #define SSIMD_SSE 1
  #include <immintrin.h>
#elif defined(__SSE__) || defined(__SSE2__)  || defined(__SSE3__)
  #define SSIMD_SSE 1
  #include <immintrin.h>
#elif defined(__ARM_NEON_FP)
  #include <arm_neon.h>
  #define SSIMD_NEON 1
#endif


#if defined (_DEBUG) || ! (defined (NDEBUG) || defined (_NDEBUG))
  #define SSIMD_DEBUG 1
#endif

#ifdef SSIMD_DEBUG
  #ifdef SSIMD_MSVC
    #define ASSERT(x) if (!(x)) __debugbreak()
  #else
    #include <cassert>
    #define ASSERT(x) assert(x)
  #endif
#else
  #define ASSERT(x)
#endif