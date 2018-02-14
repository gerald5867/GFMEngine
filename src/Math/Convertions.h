#pragma once

#define GFM_TO_DEGREES_CONSTANT 57.295779513f
#define GFM_TO_RADIANS_CONSTANT 0.0174532925f

namespace gfm
{
namespace math
{
	template<typename ReturnType = float,typename InType = float>
	constexpr ReturnType ToRadians(InType degrees) noexcept {
		return degrees * GFM_TO_RADIANS_CONSTANT;
	}

	template<typename ReturnType = float, typename InType = float>
	constexpr ReturnType ToDegrees(InType radians) noexcept {
		return radians * GFM_TO_DEGREES_CONSTANT;
	}

}// namespace math
}// namespace gfm

#undef GFM_TO_DEGREES_CONSTANT
#undef GFM_TO_RADIANS_CONSTANT