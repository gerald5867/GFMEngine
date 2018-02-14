#pragma once
#ifndef MATRIX3X3_H
#define MATRIX3X3_H
#include "Vector.h"
#include <exception>
#pragma warning(push)
#pragma warning(disable: 4544) // for Dummy Arguments seperated !
namespace gfm {
namespace math {

struct Matrix3x3
{
	using ColumType = Vector3D;
	using SkalarType = typename ColumType::SkalarType;
	union 
	{
		ColumType  colums[3];
		SkalarType elements[9];
	};

	GFM_APICALL Matrix3x3(const Matrix3x3& other) = default;
	GFM_APICALL Matrix3x3(Matrix3x3&& other) = default;
	GFM_APICALL Matrix3x3& operator = (const Matrix3x3& other) = default;
	GFM_APICALL Matrix3x3& operator = (Matrix3x3&& other) = default;
	GFM_APICALL Matrix3x3(SkalarType first = 0.0f,   SkalarType second = 0.0f,SkalarType third = 0.0f,
						  SkalarType fourth = 0.0f,  SkalarType fifth = 0.0f, SkalarType sixth = 0.0f,
						  SkalarType seventh = 0.0f, SkalarType eight = 0.0f, SkalarType nineth = 0.0f);
	GFM_APICALL Matrix3x3(const Vector3D& vec_first, const Vector3D& vec_second, const Vector3D& vec_third);
	GFM_APICALL Matrix3x3(const Vector3D& vec_first, const Vector3D& vec_second,
						  SkalarType first, SkalarType second, SkalarType third);
	GFM_APICALL Matrix3x3(const Vector3D& vec_first, SkalarType first, SkalarType second,
				  SkalarType third, SkalarType fourth, SkalarType fifth, SkalarType sixth);
	GFM_APICALL Matrix3x3(SkalarType first, SkalarType second, SkalarType third,
						  const Vector3D& vec_second, const Vector3D& vec_third);
	GFM_APICALL Matrix3x3(SkalarType first, SkalarType second, SkalarType third,
		SkalarType fourth, SkalarType fifth, SkalarType sixth, const Vector3D& vec_third);

	static GFM_APICALL Matrix3x3 RotationX(float radians);
	static GFM_APICALL Matrix3x3 RotationY(float radians);
	static GFM_APICALL Matrix3x3 RotationZ(float radians);
	static GFM_APICALL Matrix3x3 Orthographic(SkalarType left, SkalarType right, SkalarType bottom, SkalarType top);
	static GFM_APICALL Matrix3x3 Translate(const Vector3D& translate);
	static GFM_APICALL Matrix3x3 Scale(const Vector3D& scale);
	static GFM_APICALL Matrix3x3 Transpose(const Matrix3x3& mat);
	static GFM_APICALL Matrix3x3 Identity();

	GFM_APICALL void ToIdentity();

	GFM_APICALL const ColumType & operator[](size_t index) const;
	GFM_APICALL ColumType & operator[](size_t index);
	GFM_APICALL ColumType row(size_t index) const;
	GFM_APICALL ColumType col(size_t index) const;

	GFM_APICALL Matrix3x3 & operator += (const Matrix3x3 & other);
	GFM_APICALL Matrix3x3 & operator += (SkalarType skalar);

	GFM_APICALL Matrix3x3 & operator -= (const Matrix3x3 & other);
	GFM_APICALL Matrix3x3 & operator -= (SkalarType skalar);

	GFM_APICALL Matrix3x3 & operator *= (const Matrix3x3 & other);
	GFM_APICALL Matrix3x3 & operator *= (SkalarType skalar);

	GFM_APICALL Matrix3x3 & operator /= (const Matrix3x3 & other);
	GFM_APICALL Matrix3x3 & operator /= (SkalarType skalar);

	GFM_APICALL Matrix3x3 & operator ++();
	GFM_APICALL Matrix3x3 & operator --();
	GFM_APICALL Matrix3x3 operator ++(int);
	GFM_APICALL Matrix3x3 operator --(int);

};

GFM_APICALL gfm::math::Matrix3x3 operator +(const gfm::math::Matrix3x3 & mat);
GFM_APICALL gfm::math::Matrix3x3 operator +(const gfm::math::Matrix3x3& left, const gfm::math::Matrix3x3& right);
GFM_APICALL gfm::math::Matrix3x3 operator +(const gfm::math::Matrix3x3& left, gfm::math::Matrix3x3::SkalarType skalar);
GFM_APICALL gfm::math::Matrix3x3 operator +(gfm::math::Matrix3x3::SkalarType skalar, const gfm::math::Matrix3x3& right);

GFM_APICALL gfm::math::Matrix3x3 operator -(const gfm::math::Matrix3x3& mat);
GFM_APICALL gfm::math::Matrix3x3 operator -(const gfm::math::Matrix3x3& left, const gfm::math::Matrix3x3& right);
GFM_APICALL gfm::math::Matrix3x3 operator -(const gfm::math::Matrix3x3& left, gfm::math::Matrix3x3::SkalarType skalar);
GFM_APICALL gfm::math::Matrix3x3 operator -(gfm::math::Matrix3x3::SkalarType skalar, const gfm::math::Matrix3x3& right);

GFM_APICALL gfm::math::Matrix3x3 operator * (const gfm::math::Matrix3x3& left, const gfm::math::Matrix3x3& right);
GFM_APICALL gfm::math::Matrix3x3 operator * (const gfm::math::Matrix3x3& left, gfm::math::Matrix3x3::SkalarType skalar);
GFM_APICALL gfm::math::Matrix3x3 operator * (gfm::math::Matrix3x3::SkalarType skalar, const gfm::math::Matrix3x3& right);

GFM_APICALL typename gfm::math::Matrix3x3::ColumType operator * (const gfm::math::Matrix3x3& left, const typename gfm::math::Matrix3x3::ColumType& vec);
GFM_APICALL typename gfm::math::Matrix3x3::ColumType operator * (const typename gfm::math::Matrix3x3::ColumType& vec, const gfm::math::Matrix3x3 & right);

GFM_APICALL gfm::math::Matrix3x3 operator / (const gfm::math::Matrix3x3& left, const gfm::math::Matrix3x3& right);
GFM_APICALL gfm::math::Matrix3x3 operator / (const gfm::math::Matrix3x3 & left, gfm::math::Matrix3x3::SkalarType skalar);
GFM_APICALL gfm::math::Matrix3x3 operator / (gfm::math::Matrix3x3::SkalarType skalar, const gfm::math::Matrix3x3 & right);
GFM_APICALL typename gfm::math::Matrix3x3::ColumType operator / (const gfm::math::Matrix3x3 & left, const typename gfm::math::Matrix3x3::ColumType & vec);
GFM_APICALL typename gfm::math::Matrix3x3::ColumType operator / (const typename gfm::math::Matrix3x3::ColumType & vec, const gfm::math::Matrix3x3 & right);

} // namespace math
} // namespace gfm

#endif // MATRIX3X3_H