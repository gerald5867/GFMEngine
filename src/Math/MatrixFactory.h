#pragma once
#include "Matrix.h"
#include "Vector.h"

namespace gfm
{
	namespace math
	{
		template<typename VectorType = float>
		constexpr Mat3f createRotationMatrixNRadians3x3(
			float radians, Axis axis, bool clock_wise = true) noexcept
		{
			switch (axis)
			{
			case Axis::eAXIS_X:
				return detail::x3::createRotationMatrixNRadiansXAxis(radians, clock_wise);
			case Axis::eAXIS_Y:
				return detail::x3::createRotationMatrixNRadiansYAxis(radians, clock_wise);
			case Axis::eAXIS_Z:
				return detail::x3::createRotationMatrixNRadiansZAxis(radians, clock_wise);
			}
			return detail::x3::createRotationMatrixNRadiansZAxis(radians, clock_wise);
		}

		template<typename VectorType = float>
		constexpr Mat4f createRotationMatrixNRadians4x4(
			float radians, Axis axis, bool clock_wise = true) noexcept
		{
			switch (axis)
			{
			case Axis::eAXIS_X:
				return detail::x4::createRotationMatrixNRadiansXAxis(radians, clock_wise);
			case Axis::eAXIS_Y:
				return detail::x4::createRotationMatrixNRadiansYAxis(radians, clock_wise);
			case Axis::eAXIS_Z:
				return detail::x4::createRotationMatrixNRadiansZAxis(radians, clock_wise);
			}
			return detail::x4::createRotationMatrixNRadiansZAxis(radians, clock_wise);
		}

		namespace detail
		{
			namespace x4
			{
				template<typename VectorType = float>
				constexpr Mat4f createRotationMatrixNRadiansXAxis(float radians, bool clockwise = true) noexcept
				{
					float sin = std::sin(radians);
					float cos = std::cos(radians);
					return Mat4f
					(
						Vector4D<VectorType>(1, 0, 0, 0),
						Vector4D<VectorType>(0, cos, (clockwise) ? -sin : sin, 0),
						Vector4D<VectorType>(0, (clockwise) ? sin : -sin, cos, 0),
						Vector4D<VectorType>(0, 0, 0, 0)
					);
				}

				template<typename VectorType = float>
				constexpr Mat4f createRotationMatrixNRadiansYAxis(float radians, bool clockwise = true) noexcept
				{
					float sin = std::sin(radians);
					float cos = std::cos(radians);
					return Mat4f
					(
						Vector4D<VectorType>(cos, 0, (clockwise) ? sin : -sin, 0),
						Vector4D<VectorType>(0, 1, 0, 0),
						Vector4D<VectorType>((clockwise) ? -sin : sin, 0, cos, 0),
						Vector4D<VectorType>(0, 0, 0, 0)
					);
				}

				template<typename VectorType = float>
				constexpr Mat4f createRotationMatrixNRadiansZAxis(float radians, bool clockwise = true) noexcept
				{
					float sin = std::sin(radians);
					float cos = std::cos(radians);
					return Mat4f
					(
						Vector4D<VectorType>(cos, (clockwise) ? -sin : sin, 0, 0),
						Vector4D<VectorType>((clockwise) ? sin : -sin, cos, 0, 0),
						Vector4D<VectorType>(0, 0, 1, 0),
						Vector4D<VectorType>(0, 0, 0, 0)
					);
				}
			}
		}

	} // namespace math

} // namespace gfm

