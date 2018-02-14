#pragma once
#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <cmath>
#include "Vector2D.h"
#include "..\Macro\ApiCall.h"
#include "Constants.h"
namespace gfm
{
namespace math
{
	struct Vector3D
	{
		using SkalarType = float;
		union
		{
			struct
			{
				SkalarType x;
				SkalarType y;
				SkalarType z;
			};
			struct
			{
				SkalarType r;
				SkalarType g;
				SkalarType b;
			};
			struct
			{
				SkalarType u;
				SkalarType v;
				SkalarType w;
			};
		};
		GFM_APICALL Vector3D() = default;
		GFM_APICALL Vector3D(SkalarType x);
		GFM_APICALL Vector3D(SkalarType x, SkalarType y);
		GFM_APICALL Vector3D(SkalarType x, SkalarType y, SkalarType z);
		GFM_APICALL Vector3D(const Vector2D& vec, SkalarType skalar);
		GFM_APICALL Vector3D(SkalarType skalar,const Vector2D & vec);

		GFM_APICALL Vector3D(const Vector3D& other)		         = default;
		GFM_APICALL Vector3D(Vector3D&& other)				     = default;
		GFM_APICALL Vector3D& operator = (const Vector3D& other) = default;
		GFM_APICALL Vector3D& operator = (Vector3D&& other)	     = default;

		GFM_APICALL Vector3D& operator += (SkalarType skalar) noexcept;
		GFM_APICALL Vector3D& operator += (const Vector3D& vector) noexcept;

		GFM_APICALL Vector3D & operator -= (SkalarType skalar) noexcept;
		GFM_APICALL Vector3D & operator -= (const Vector3D& vector) noexcept;

		GFM_APICALL Vector3D & operator *= (SkalarType skalar) noexcept;
		GFM_APICALL Vector3D & operator *= (const Vector3D& vector) noexcept;

		GFM_APICALL Vector3D & operator /= (SkalarType skalar);
		GFM_APICALL Vector3D & operator /= (const Vector3D& vector);


		GFM_APICALL Vector3D & operator ++ () noexcept;
		GFM_APICALL Vector3D & operator -- () noexcept;
		GFM_APICALL Vector3D operator ++ (int) noexcept;
		GFM_APICALL Vector3D operator -- (int) noexcept;

		GFM_APICALL SkalarType & operator [](size_t index);
		GFM_APICALL const SkalarType & operator [](size_t index) const;

	#ifdef _MSC_VER
		#pragma region SwizzleOperators
	#endif
		GFM_APICALL Vector2D xx()  const noexcept;
		GFM_APICALL Vector2D xy()  const noexcept;
		GFM_APICALL Vector2D xz()  const noexcept;
		GFM_APICALL Vector2D yx()  const noexcept;
		GFM_APICALL Vector2D yy()  const noexcept;
		GFM_APICALL Vector2D yz()  const noexcept;
		GFM_APICALL Vector2D zx()  const noexcept;
		GFM_APICALL Vector2D zy()  const noexcept;
		GFM_APICALL Vector2D zz()  const noexcept;
		GFM_APICALL Vector3D xxx() const noexcept;
		GFM_APICALL Vector3D xxy() const noexcept;
		GFM_APICALL Vector3D xxz() const noexcept;
		GFM_APICALL Vector3D xyx() const noexcept;
		GFM_APICALL Vector3D xyy() const noexcept;
		GFM_APICALL Vector3D xyz() const noexcept;
		GFM_APICALL Vector3D xzx() const noexcept;
		GFM_APICALL Vector3D xzy() const noexcept;
		GFM_APICALL Vector3D xzz() const noexcept;
		GFM_APICALL Vector3D yxx() const noexcept;
		GFM_APICALL Vector3D yxy() const noexcept;
		GFM_APICALL Vector3D yxz() const noexcept;
		GFM_APICALL Vector3D yyx() const noexcept;
		GFM_APICALL Vector3D yyy() const noexcept;
		GFM_APICALL Vector3D yyz() const noexcept;
		GFM_APICALL Vector3D yzx() const noexcept;
		GFM_APICALL Vector3D yzy() const noexcept;
		GFM_APICALL Vector3D yzz() const noexcept;
		GFM_APICALL Vector3D zxx() const noexcept;
		GFM_APICALL Vector3D zxy() const noexcept;
		GFM_APICALL Vector3D zxz() const noexcept;
		GFM_APICALL Vector3D zyx() const noexcept;
		GFM_APICALL Vector3D zyy() const noexcept;
		GFM_APICALL Vector3D zyz() const noexcept;
		GFM_APICALL Vector3D zzx() const noexcept;
		GFM_APICALL Vector3D zzy() const noexcept;
		GFM_APICALL Vector3D zzz() const noexcept;

	#ifdef _MSC_VER
	#pragma endregion SwizzleOperators
	#endif

		GFM_APICALL Vector3D Cross(const Vector3D& other) const noexcept;
		GFM_APICALL SkalarType Dot(const Vector3D& vec) const noexcept;

		GFM_APICALL Vector3D RotateClockwise(float radians, Axis axis) const noexcept;
		GFM_APICALL Vector3D RotateCounterClockwise(float radians, Axis axis) const noexcept;
		GFM_APICALL Vector3D Normalize() const noexcept;
		GFM_APICALL Vector3D Abs()   const noexcept;
		GFM_APICALL SkalarType Length()const noexcept;
		GFM_APICALL SkalarType LengthSq() const noexcept;
		GFM_APICALL SkalarType Min()   const noexcept;
		GFM_APICALL SkalarType Max()   const noexcept;
		GFM_APICALL SkalarType Sum()   const noexcept;
		GFM_APICALL SkalarType Angle() const noexcept;
		GFM_APICALL bool IsZero() const noexcept;
	};

	GFM_APICALL gfm::math::Vector3D operator + (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept;
	GFM_APICALL gfm::math::Vector3D operator + (gfm::math::Vector3D::SkalarType skalar, const gfm::math::Vector3D& right) noexcept;
	GFM_APICALL gfm::math::Vector3D operator + (const gfm::math::Vector3D& left, gfm::math::Vector3D::SkalarType skalar) noexcept;
	GFM_APICALL gfm::math::Vector3D operator + (const gfm::math::Vector3D& vec) noexcept;

	GFM_APICALL gfm::math::Vector3D operator - (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right);
	GFM_APICALL gfm::math::Vector3D operator - (gfm::math::Vector3D::SkalarType skalar, const gfm::math::Vector3D& right) noexcept;
	GFM_APICALL gfm::math::Vector3D operator - (const gfm::math::Vector3D& left, gfm::math::Vector3D::SkalarType skalar) noexcept;
	GFM_APICALL gfm::math::Vector3D operator - (const gfm::math::Vector3D& vec) noexcept;

	GFM_APICALL gfm::math::Vector3D operator * (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept;
	GFM_APICALL gfm::math::Vector3D operator * (gfm::math::Vector3D::SkalarType skalar, const gfm::math::Vector3D& right) noexcept;
	GFM_APICALL gfm::math::Vector3D operator * (const gfm::math::Vector3D& left, gfm::math::Vector3D::SkalarType skalar) noexcept;

	GFM_APICALL gfm::math::Vector3D operator / (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right);
	GFM_APICALL gfm::math::Vector3D operator / (gfm::math::Vector3D::SkalarType skalar, const gfm::math::Vector3D& right);
	GFM_APICALL gfm::math::Vector3D operator / (const gfm::math::Vector3D & left, gfm::math::Vector3D::SkalarType skalar);

	GFM_APICALL bool operator || (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept;
	GFM_APICALL bool operator && (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept;
	GFM_APICALL bool operator == (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept;
	GFM_APICALL bool operator != (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept;

} // namespace math	
} // namespace gfm

#endif // VECTOR3D_H
