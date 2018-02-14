#pragma once
#ifndef MATRIX2X2_H
#define MATRIX2X2_H
#include "Vector.h"

namespace gfm {
namespace math {
struct Matrix2x2
{
	using ColumType = Vector2D;
	using SkalarType = typename ColumType::SkalarType;
	union 
	{
		ColumType   colums[2];
		SkalarType elements[4];
	};

	GFM_APICALL Matrix2x2() = default;
	GFM_APICALL Matrix2x2(const Matrix2x2 & other)			    = default;
	GFM_APICALL Matrix2x2(Matrix2x2 && other)				    = default;
	GFM_APICALL Matrix2x2& operator = (const Matrix2x2 & other) = default;
	GFM_APICALL Matrix2x2& operator = (Matrix2x2 && other)      = default;

	GFM_APICALL Matrix2x2(SkalarType first, SkalarType second, SkalarType third, SkalarType fourth);
	GFM_APICALL Matrix2x2(SkalarType first, SkalarType second, SkalarType third);
	GFM_APICALL Matrix2x2(SkalarType first, SkalarType second);
	GFM_APICALL Matrix2x2(SkalarType first);
	GFM_APICALL Matrix2x2(const Vector2D& first, const Vector2D& second);
	GFM_APICALL Matrix2x2(const Vector2D& left, SkalarType first, SkalarType second);

	GFM_APICALL Matrix2x2(SkalarType first, const Vector2D& middle, SkalarType second);
	GFM_APICALL Matrix2x2(SkalarType first, SkalarType second, const Vector2D& right);
	GFM_APICALL Matrix2x2(SkalarType skalar, const Vector3D& right);
	GFM_APICALL Matrix2x2(const Vector3D& left, SkalarType skalar);
	GFM_APICALL Matrix2x2(const Vector4D& vec);

	static GFM_APICALL Matrix2x2 Rotation(float radians, bool clock_wise = true) noexcept;
	static GFM_APICALL Matrix2x2 Orthographic(SkalarType left, SkalarType right, SkalarType bottom, SkalarType top);
	static GFM_APICALL Matrix2x2 Translate(const Vector2D& translate);
	static GFM_APICALL Matrix2x2 Scale(const Vector2D& scale);
	static GFM_APICALL Matrix2x2 Transpose(const Matrix2x2& mat);
	static GFM_APICALL Matrix2x2 Identity();

	GFM_APICALL void ToIdentity();

	GFM_APICALL const ColumType & operator[](size_t index) const;
	GFM_APICALL ColumType & operator[](size_t index);
	GFM_APICALL ColumType row(size_t index) const;
	GFM_APICALL ColumType col(size_t index) const;

	GFM_APICALL Matrix2x2 & operator += (const Matrix2x2 & other);
	GFM_APICALL Matrix2x2 & operator += (SkalarType skalar);
	GFM_APICALL Matrix2x2 & operator -= (const Matrix2x2 & other);
	GFM_APICALL Matrix2x2 & operator -= (SkalarType skalar);
	GFM_APICALL Matrix2x2 & operator *= (const Matrix2x2 & other);
	GFM_APICALL Matrix2x2 & operator *= (SkalarType skalar);
	GFM_APICALL Matrix2x2 & operator /= (const Matrix2x2 & other);
	GFM_APICALL Matrix2x2 & operator /= (SkalarType skalar);

	GFM_APICALL Matrix2x2 & operator ++();
	GFM_APICALL Matrix2x2 & operator --();
	GFM_APICALL Matrix2x2 operator ++(int);
	GFM_APICALL Matrix2x2 operator --(int);

};

GFM_APICALL gfm::math::Matrix2x2 operator +(const gfm::math::Matrix2x2 & mat);
GFM_APICALL gfm::math::Matrix2x2 operator +(const gfm::math::Matrix2x2& left, const gfm::math::Matrix2x2& right);
GFM_APICALL gfm::math::Matrix2x2 operator +(const gfm::math::Matrix2x2& left, gfm::math::Matrix2x2::SkalarType skalar);
GFM_APICALL gfm::math::Matrix2x2 operator +(gfm::math::Matrix2x2::SkalarType skalar, const gfm::math::Matrix2x2& right);

GFM_APICALL gfm::math::Matrix2x2 operator -(const gfm::math::Matrix2x2& mat);
GFM_APICALL gfm::math::Matrix2x2 operator -(const gfm::math::Matrix2x2& left, const gfm::math::Matrix2x2& right);
GFM_APICALL gfm::math::Matrix2x2 operator -(const gfm::math::Matrix2x2& left, gfm::math::Matrix2x2::SkalarType skalar);
GFM_APICALL gfm::math::Matrix2x2 operator -(gfm::math::Matrix2x2::SkalarType skalar, const gfm::math::Matrix2x2& right);

GFM_APICALL gfm::math::Matrix2x2 operator * (const gfm::math::Matrix2x2& left, const gfm::math::Matrix2x2& right);
GFM_APICALL gfm::math::Matrix2x2 operator * (const gfm::math::Matrix2x2& left, gfm::math::Matrix2x2::SkalarType skalar);
GFM_APICALL gfm::math::Matrix2x2 operator * (gfm::math::Matrix2x2::SkalarType skalar, const gfm::math::Matrix2x2 & right);
GFM_APICALL gfm::math::Vector2D  operator * (const gfm::math::Matrix2x2& left, const gfm::math::Vector2D& vec);
GFM_APICALL gfm::math::Vector2D  operator * (const gfm::math::Vector2D& vec, const gfm::math::Matrix2x2 & right);

GFM_APICALL gfm::math::Matrix2x2 operator / (const gfm::math::Matrix2x2& left, const gfm::math::Matrix2x2& right);
GFM_APICALL gfm::math::Matrix2x2 operator / (const gfm::math::Matrix2x2& left, gfm::math::Matrix2x2::SkalarType skalar);
GFM_APICALL gfm::math::Matrix2x2 operator / (gfm::math::Matrix2x2::SkalarType skalar, const gfm::math::Matrix2x2& right);

GFM_APICALL typename gfm::math::Matrix2x2::ColumType operator / (const gfm::math::Matrix2x2& left, const typename gfm::math::Matrix2x2::ColumType& vec);
GFM_APICALL typename gfm::math::Matrix2x2::ColumType operator / (const typename gfm::math::Matrix2x2::ColumType & vec, const gfm::math::Matrix2x2 & right);

} // namespace math
} // namespace gfm


#endif // MATRIX2X2_H