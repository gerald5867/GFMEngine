#pragma once
#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>
#include "..\Macro\ApiCall.h"

namespace gfm{
namespace math
{
	struct Matrix2x2;
	struct Vector2D
	{
		using SkalarType = float;
		union 
		{
			struct 
			{
				SkalarType x;
				SkalarType y;
			};
			struct
			{
				SkalarType r;
				SkalarType g;
			};
			struct
			{
				SkalarType u;
				SkalarType v;
			};
		};

		GFM_APICALL Vector2D(SkalarType x, SkalarType y );
		GFM_APICALL Vector2D() = default;
		GFM_APICALL Vector2D(SkalarType skalar);
		GFM_APICALL Vector2D(const Vector2D& other)				  = default;
		GFM_APICALL Vector2D(Vector2D&& other)					  = default;
		GFM_APICALL Vector2D & operator = (const Vector2D& other) = default;
		GFM_APICALL Vector2D & operator = (Vector2D&& other)	  = default;

		GFM_APICALL Vector2D& operator += (SkalarType skalar) noexcept;
		GFM_APICALL Vector2D& operator += (const Vector2D & vector) noexcept;

		GFM_APICALL Vector2D& operator -= (SkalarType skalar) noexcept;
		GFM_APICALL Vector2D& operator -= (const Vector2D& vector) noexcept;

		GFM_APICALL Vector2D& operator *= (SkalarType skalar) noexcept;
		GFM_APICALL Vector2D& operator *= (const Vector2D & vector) noexcept;
		GFM_APICALL Vector2D& operator *= (const Matrix2x2& mat) noexcept;


		GFM_APICALL Vector2D& operator /= (SkalarType skalar);
		GFM_APICALL Vector2D& operator /= (const Vector2D& vector);

		GFM_APICALL Vector2D & operator ++ () noexcept;
		GFM_APICALL Vector2D & operator -- () noexcept;
		GFM_APICALL Vector2D operator ++ (int) noexcept;
		GFM_APICALL Vector2D operator -- (int) noexcept;

		GFM_APICALL Vector2D xx() const noexcept;
		GFM_APICALL Vector2D yy() const noexcept;
		GFM_APICALL Vector2D xy() const noexcept;
		GFM_APICALL Vector2D yx() const noexcept;

		GFM_APICALL SkalarType& operator [](size_t index);
		GFM_APICALL const SkalarType& operator [](size_t index) const;

		GFM_APICALL SkalarType Cross(const Vector2D& other) const noexcept;
		GFM_APICALL SkalarType Dot(const Vector2D& vec) const noexcept;

		GFM_APICALL Vector2D RotateClockwise(SkalarType radians) const noexcept;
		GFM_APICALL Vector2D RotateCounterClockwise(SkalarType radians) const noexcept;
		GFM_APICALL Vector2D Normalize() const noexcept;
		GFM_APICALL Vector2D Abs()   const noexcept;

		GFM_APICALL SkalarType Length()const noexcept;
		GFM_APICALL SkalarType LengthSq() const noexcept;
		GFM_APICALL SkalarType Min()   const noexcept;
		GFM_APICALL SkalarType Max()   const noexcept;
		GFM_APICALL SkalarType Sum()   const noexcept;
		GFM_APICALL SkalarType Angle() const noexcept;
		GFM_APICALL bool IsZero() const noexcept;
	};

	GFM_APICALL gfm::math::Vector2D operator * (const gfm::math::Vector2D& left, const gfm::math::Vector2D& right) noexcept;
	GFM_APICALL gfm::math::Vector2D operator * (gfm::math::Vector2D::SkalarType skalar, const gfm::math::Vector2D& right) noexcept;
	GFM_APICALL gfm::math::Vector2D operator * (const gfm::math::Vector2D& left, gfm::math::Vector2D::SkalarType skalar) noexcept;
	
	GFM_APICALL gfm::math::Vector2D operator + (const gfm::math::Vector2D& left, const gfm::math::Vector2D& right) noexcept;
	GFM_APICALL gfm::math::Vector2D operator + (gfm::math::Vector2D::SkalarType skalar, const gfm::math::Vector2D& right) noexcept;
	GFM_APICALL gfm::math::Vector2D operator + (const gfm::math::Vector2D& left, gfm::math::Vector2D::SkalarType skalar) noexcept;
	GFM_APICALL gfm::math::Vector2D operator + (const gfm::math::Vector2D& vec) noexcept;

	GFM_APICALL gfm::math::Vector2D operator - (const gfm::math::Vector2D& left, const gfm::math::Vector2D& right);
	GFM_APICALL gfm::math::Vector2D operator - (gfm::math::Vector2D::SkalarType skalar, const gfm::math::Vector2D& right) noexcept;
	GFM_APICALL gfm::math::Vector2D operator - (const gfm::math::Vector2D& left, gfm::math::Vector2D::SkalarType skalar) noexcept;
	GFM_APICALL gfm::math::Vector2D operator - (const gfm::math::Vector2D& vec) noexcept;

	GFM_APICALL gfm::math::Vector2D operator * (const gfm::math::Vector2D& left, const gfm::math::Vector2D& right) noexcept;
	GFM_APICALL gfm::math::Vector2D operator * (gfm::math::Vector2D::SkalarType skalar, const gfm::math::Vector2D& right) noexcept;
	GFM_APICALL gfm::math::Vector2D operator * (const gfm::math::Vector2D& left, gfm::math::Vector2D::SkalarType skalar) noexcept;

	GFM_APICALL gfm::math::Vector2D operator / (const gfm::math::Vector2D& left, const gfm::math::Vector2D& right);
	GFM_APICALL gfm::math::Vector2D operator / (gfm::math::Vector2D::SkalarType skalar, const gfm::math::Vector2D& right);
	GFM_APICALL gfm::math::Vector2D operator / (const gfm::math::Vector2D& left, gfm::math::Vector2D::SkalarType skalar);

	GFM_APICALL bool operator || (const gfm::math::Vector2D & left, const gfm::math::Vector2D & right) noexcept;
	GFM_APICALL bool operator && (const gfm::math::Vector2D& left, const gfm::math::Vector2D& right) noexcept;
	GFM_APICALL bool operator == (const gfm::math::Vector2D& left, const gfm::math::Vector2D & right) noexcept;
	GFM_APICALL bool operator != (const gfm::math::Vector2D & left, const gfm::math::Vector2D & right) noexcept;

} // namespace math	
} // namespace gfm

#endif // VECTOR2D_H


