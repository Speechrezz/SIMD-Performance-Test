#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) 
  #define SSIMD_WINDOWS 1
#elif defined __APPLE__
  #define SSIMD_APPLE 1
#else
  #error "System NOT supported"
#endif

#if defined(_MSC_VER)
  #define SSIMD_MSVC
#endif

#if defined(__AVX__) || defined(__AVX2__)
  #define SSIMD_AVX 1
  #define SSIMD_SSE 1
#elif defined(__SSE__) || defined(__SSE2__)  || defined(__SSE3__)
  #define SSIMD_SSE 1
#endif