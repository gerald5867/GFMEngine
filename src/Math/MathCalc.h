#pragma once
#include "../Application.h"
namespace gfm
{
	namespace math
	{
		GFM_BEST_INLINE Vec2 ToDeviceCoordinates(float x, float y) {
			return {
				x / Application::instance().GetWidth()  * 2.0f - 1.0f,
				y / Application::instance().GetHeight() * 2.0f - 1.0f
			};
		}

		GFM_BEST_INLINE Vec2 ToDeviceCoordinates(Vec2 coordinates) {
			return {
				coordinates.x / Application::instance().GetWidth()  * 2.0f - 1.0f,
				coordinates.y / Application::instance().GetHeight() * 2.0f - 1.0f
			};
		}
		
		GFM_BEST_INLINE float DeviceWidthToWindowWidth(float width) {
			return width * Application::instance().GetWidth() / 2 + 1.0f;
		}

		GFM_BEST_INLINE float DeviceHeightToWindowHeight(float height) {
			return (Application::instance().GetWidth() / 2 ) *  (height + 1.0f);
		}

		GFM_BEST_INLINE float WindowWidthToDeviceWith(float width) {
			return width / Application::instance().GetWidth() * 2.0f - 1.0f;
		}

		GFM_BEST_INLINE float WindowHeightToDeviceHeight(float height) {
			return height / Application::instance().GetHeight() * 2.0f - 1.0f;
		}

		template<typename IntegralType>
		constexpr IntegralType Nearest(IntegralType value, IntegralType first, IntegralType second) noexcept {
			IntegralType firstDistance = (value > first) ? value - first   : first - value;
			IntegralType secondDistance = (value > second) ? value - second : second - value;
			if (firstDistance < secondDistance) {
				return first;
			}
			else if (firstDistance > secondDistance) {
				return second;
			}
			return value;
		}
	}//namespace math
}//namespacs