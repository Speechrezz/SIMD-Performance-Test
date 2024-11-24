#pragma once

#include <cmath>

namespace ssimd::generic
{

template<typename Register>
inline Register sin(const Register& reg)
{
	// TODO: Come up with a better generic implementation
	alignas(Register::size()) float arr[Register::size()];
	reg.storeAligned(arr);

	for (float& v : arr)
		v = std::sin(v);

	return Register::loadAligned(arr);
}

} // namespace ssimd::generic
