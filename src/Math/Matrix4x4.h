#pragma once
#include "Vector.h"
#ifndef MATRIX4X4_H
#define MATRIX4X4_H
namespace gfm {
namespace math {
struct Matrix4x4
{
	using ColumType = Vector4D;
	using SkalarType = typename ColumType::SkalarType;
	union 
	{
		ColumType  colums[4];
		SkalarType elements[16];
	};

	GFM_APICALL Matrix4x4(const Matrix4x4& other)			   = default;
	GFM_APICALL Matrix4x4(Matrix4x4&& other)				   = default;
	GFM_APICALL Matrix4x4& operator = (const Matrix4x4& other) = default;
	GFM_APICALL Matrix4x4& operator = (Matrix4x4&& other)	   = default;

	GFM_APICALL Matrix4x4(SkalarType first = 0.0f,     SkalarType second = 0.0f,  SkalarType third = 0.0f,    SkalarType firth = 0.0f,
						  SkalarType fifth = 0.0f,     SkalarType sixth = 0.0f,   SkalarType seventh = 0.0f,  SkalarType eight = 0.0f,
						  SkalarType nineth = 0.0f,    SkalarType ten = 0.0f,     SkalarType eleven = 0.0f,   SkalarType twelve = 0.0f,
						  SkalarType thirtheen = 0.0f, SkalarType forteen = 0.0f, SkalarType fiftheen = 0.0f, SkalarType sixteen = 0.0f);

	GFM_APICALL Matrix4x4(const Vector4D& vec_first, const Vector4D& vec_second, const Vector4D& vec_third, const Vector4D& vec_fourth);
	GFM_APICALL Matrix4x4(const Vector4D& vec_first, SkalarType first, SkalarType second, SkalarType third,  SkalarType fourth, 
													 SkalarType fifth, SkalarType sixth,  SkalarType seven,  SkalarType eight, 
													 SkalarType nineth, SkalarType ten, SkalarType eleven, SkalarType twelve);

	GFM_APICALL Matrix4x4(const Vector4D& vec_first, const Vector4D& vec_second,
						  SkalarType first, SkalarType second, SkalarType third, SkalarType fourth, 
						  SkalarType fifth, SkalarType sixth, SkalarType seventh, SkalarType eight);

	GFM_APICALL Matrix4x4(const Vector4D& vec_first, const Vector4D& vec_second, const Vector4D& vec_third, 
						  SkalarType first, SkalarType second, SkalarType third, SkalarType fourth);

	GFM_APICALL Matrix4x4(SkalarType first, SkalarType second, SkalarType third, SkalarType fourth,
						  const Vector4D& vec_first, const Vector4D& vec_second, const Vector4D& vec_third);

	GFM_APICALL Matrix4x4(SkalarType first, SkalarType second, SkalarType third, SkalarType fourth, 
						  SkalarType fifth, SkalarType sixth,  SkalarType seven, SkalarType eigtht,
						  const Vector4D& vec_second, const Vector4D& vec_third);

	GFM_APICALL Matrix4x4(SkalarType first, SkalarType second, SkalarType third,  SkalarType fourth, 
						  SkalarType fifth, SkalarType sixth,  SkalarType seven,  SkalarType eight, 
						  SkalarType nine,  SkalarType ten,	   SkalarType eleven, SkalarType twelve, 
						  const Vector4D& vec_fourth);

	static GFM_APICALL Matrix4x4 Perspective(SkalarType fov, SkalarType aspectRatio, SkalarType near, SkalarType far);
	static GFM_APICALL Matrix4x4 Rotation(float radians, const Vec3& axis);
	static GFM_APICALL Matrix4x4 Orthographic(SkalarType left, SkalarType right, SkalarType bottom, SkalarType top);
	static GFM_APICALL Matrix4x4 Orthographic(SkalarType left, SkalarType right, SkalarType bottom, SkalarType top, SkalarType near, SkalarType far);
	static GFM_APICALL Matrix4x4 Translate(const Vector3D& translate);
	static GFM_APICALL Matrix4x4 Scale(const Vector3D& scale);
	static GFM_APICALL Matrix4x4 Transpose(const Matrix4x4& mat);
	static GFM_APICALL Matrix4x4 Identity();

	GFM_APICALL void ToIdentity();
	GFM_APICALL const ColumType& operator[](size_t index) const;
	GFM_APICALL ColumType& operator[](size_t index);
	GFM_APICALL const ColumType& Row(size_t index) const;
	GFM_APICALL const ColumType Col(size_t index) const;

	GFM_APICALL Matrix4x4& operator += (const Matrix4x4 & other);
	GFM_APICALL Matrix4x4& operator += (SkalarType skalar);

	GFM_APICALL Matrix4x4& operator -= (const Matrix4x4 & other);
	GFM_APICALL Matrix4x4& operator -= (SkalarType skalar);

	GFM_APICALL Matrix4x4 & operator *= (const Matrix4x4 & other);
	GFM_APICALL Matrix4x4 & operator *= (SkalarType skalar);

	GFM_APICALL Matrix4x4 & operator /= (const Matrix4x4 & other);
	GFM_APICALL Matrix4x4 & operator /= (SkalarType skalar);

	GFM_APICALL Matrix4x4 & operator ++();
	GFM_APICALL Matrix4x4 & operator --();
	GFM_APICALL Matrix4x4 operator ++(int);
	GFM_APICALL Matrix4x4 operator --(int);

};

GFM_APICALL gfm::math::Matrix4x4 operator +(const gfm::math::Matrix4x4 & mat);
GFM_APICALL gfm::math::Matrix4x4 operator +(const gfm::math::Matrix4x4& left, const gfm::math::Matrix4x4& right);
GFM_APICALL gfm::math::Matrix4x4 operator +(const gfm::math::Matrix4x4& left, gfm::math::Matrix4x4::SkalarType skalar);
GFM_APICALL gfm::math::Matrix4x4 operator +(gfm::math::Matrix4x4::SkalarType  skalar, const gfm::math::Matrix4x4& right);

GFM_APICALL gfm::math::Matrix4x4 operator -(const gfm::math::Matrix4x4& mat);
GFM_APICALL gfm::math::Matrix4x4 operator -(const gfm::math::Matrix4x4& left, const gfm::math::Matrix4x4& right);
GFM_APICALL gfm::math::Matrix4x4 operator -(const gfm::math::Matrix4x4& left, gfm::math::Matrix4x4::SkalarType  skalar);
GFM_APICALL gfm::math::Matrix4x4 operator -(gfm::math::Matrix4x4::SkalarType  skalar, const gfm::math::Matrix4x4& right);

GFM_APICALL gfm::math::Matrix4x4 operator * (const gfm::math::Matrix4x4& left, const gfm::math::Matrix4x4& right);
GFM_APICALL gfm::math::Matrix4x4 operator * (const gfm::math::Matrix4x4& left, gfm::math::Matrix4x4::SkalarType  skalar);
GFM_APICALL gfm::math::Matrix4x4 operator * (gfm::math::Matrix4x4::SkalarType  skalar, const gfm::math::Matrix4x4& right);
GFM_APICALL typename gfm::math::Matrix4x4::ColumType operator * (const gfm::math::Matrix4x4& left, const typename gfm::math::Matrix4x4::ColumType & vec);
GFM_APICALL typename gfm::math::Matrix4x4::ColumType operator * (const typename gfm::math::Matrix4x4::ColumType & vec, const gfm::math::Matrix4x4& right);

GFM_APICALL gfm::math::Matrix4x4 operator / (const gfm::math::Matrix4x4& left, const gfm::math::Matrix4x4& right);
GFM_APICALL gfm::math::Matrix4x4 operator / (const gfm::math::Matrix4x4& left, gfm::math::Matrix4x4::SkalarType  skalar);
GFM_APICALL gfm::math::Matrix4x4 operator / (gfm::math::Matrix4x4::SkalarType skalar, const gfm::math::Matrix4x4& right);
GFM_APICALL typename gfm::math::Matrix4x4::ColumType operator / (const gfm::math::Matrix4x4& left, const typename gfm::math::Matrix4x4::ColumType & vec);
GFM_APICALL typename gfm::math::Matrix4x4::ColumType operator / (const typename gfm::math::Matrix4x4::ColumType & vec, const gfm::math::Matrix4x4& right);


} // namespace math
} // namespace gfm
#endif // MATRIX4X4_H
