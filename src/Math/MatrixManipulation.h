#pragma once

#include "Vector.h"
#include "Convertions.h"
#include "Matrix.h"
#include <cmath>

namespace gfm
{
namespace math
{	
	template<typename VectorType = float>
	constexpr Vector2D<VectorType> rotateVectorNRadians(
		const Vector2D<VectorType> & vec, float radians, bool clock_wise = true) noexcept
	{
		float sin = std::sin(radians);
		float cos = std::cos(radians);
		return Vector2D<VectorType>
		(
			x * cos + ((clock_wise) ? -y * sin : y * sin),
			((clock_wise) ? x * sin : -x * sin ) + x * cos
		);
	}

	template<typename VectorType = float>
	constexpr Vector2D<VectorType> rotateVectorNDegrees(
		const Vector2D<VectorType> & vec, int degrees, bool clock_wise = true) noexcept
	{
		return rotateVectorNRadians(vec, toRadians(degrees), clock_wise);
	}



}//namespace math
}//namespace gfm