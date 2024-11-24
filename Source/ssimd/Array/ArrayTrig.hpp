#pragma once

#include "../Register/AllRegisters.hpp"

namespace ssimd
{
namespace array
{

// Assumes array length is multiple of 8.
template<RegisterType arch = bestArch>
inline void sin8(const float* input, float* output, size_t length)
{
	ASSERT(length % 8 == 0);

#ifdef SSIMD_APPLE
    const int lengthInt = static_cast<int>(length);
    vvsinf(output, input, &lengthInt);
#else
    using Register = ssimd::Register<arch>;

    for (size_t i = 0; i < length; i += Register::size())
    {
        Register in = Register::loadAligned(input + i);
        in = ssimd::sin(in);
        in.storeAligned(output + i);
    }
#endif
}

} // namespace array
} // namespace ssimd