//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct cyl_bessel_i1_t : elementwise_callable<cyl_bessel_i1_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(cyl_bessel_i1_t, cyl_bessel_i1_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var cyl_bessel_i1
//!   @brief `elementwise_callable` object computing the modified Bessel function of the first kind,
//!   \f$ I_1(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}\cos\tau\,\mathrm{d}\tau\f$.
//!
//!   It is the solution of  \f$ x^{2}y''+xy'-(1+x^2)y=0\f$ for which \f$ y(0) = 0\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/bessel.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto cyl_bessel_i1(floating_value auto x) -> decltype(x)           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cyl_bessel_i1[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cyl_bessel_i1[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [Floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. The value of  \f$ \displaystyle I_1(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}
//!        \cos\tau\,\mathrm{d}\tau\f$ is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: cyl_bessel_i](https://en.cppreference.com/w/cpp/numeric/special_functions/cyl_bessel_i)
//!   *  [Wikipedia: Bessel Functions](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Modified Bessel Functions](https://dlmf.nist.gov/10.25)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/bessel/cyl_bessel_i1.cpp}
//================================================================================================
  inline constexpr auto cyl_bessel_i1 = functor<cyl_bessel_i1_t>;
//================================================================================================
//! @}
//================================================================================================

}

#include <eve/module/bessel/regular/impl/cyl_bessel_i1.hpp>