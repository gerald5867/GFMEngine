#pragma once
#include <utility>
#include <stdexcept>
#include "Matrix3x3.h"
#include "..\Macro\Assertions.h"
#include "Convertions.h"
#include "..\GPUApi\Context.h"


gfm::math::Matrix3x3::Matrix3x3(SkalarType first,   SkalarType second, SkalarType third, 
								SkalarType fourth,  SkalarType fifth,  SkalarType sixth, 
							    SkalarType seventh, SkalarType eight,  SkalarType nineth) {
	colums[0][0] = first;
	colums[0][1] = second;
	colums[0][2] = third;
	colums[1][0] = fourth;
	colums[1][1] = fifth;
	colums[1][2] = sixth;
	colums[2][0] = seventh;
	colums[2][1] = eight;
	colums[2][2] = nineth;
}

gfm::math::Matrix3x3::Matrix3x3(const Vector3D& vec_first, const Vector3D& vec_second, const Vector3D& vec_third) {
	colums[0] = vec_first;
	colums[1] = vec_second;
	colums[2] = vec_third;
}

gfm::math::Matrix3x3::Matrix3x3(const Vector3D& vec_first, const Vector3D& vec_second,
							 SkalarType first, SkalarType second, SkalarType third) {
	colums[0] = vec_first;
	colums[1] = vec_second;
	colums[2][0] = first;
	colums[2][1] = second;
	colums[2][2] = third;
}

gfm::math::Matrix3x3::Matrix3x3(const Vector3D& vec_first, SkalarType first, SkalarType second,
								SkalarType third, SkalarType fourth, SkalarType fifth, SkalarType sixth) {
	colums[0] = vec_first;
	colums[1][0] = first;
	colums[1][1] = second;
	colums[1][2] = third;
	colums[2][0] = fourth;
	colums[2][1] = fifth;
	colums[2][2] = sixth;
}

gfm::math::Matrix3x3::Matrix3x3(SkalarType first, SkalarType second, SkalarType third,
							    const Vector3D& vec_second, const Vector3D& vec_third) {
	colums[0][0] = first;
	colums[0][1] = second;
	colums[0][2] = third;
	colums[1] = vec_second;
	colums[2] = vec_third;
}

gfm::math::Matrix3x3::Matrix3x3(SkalarType first, SkalarType second, SkalarType third, SkalarType fourth, 
							    SkalarType fifth, SkalarType sixth, const Vector3D& vec_third) {
	colums[0][0] = first;
	colums[0][1] = second;
	colums[0][2] = third;
	colums[1][0] = fourth;
	colums[1][1] = fifth;
	colums[1][2] = sixth;
	colums[2] = vec_third;
}

gfm::math::Matrix3x3 gfm::math::Matrix3x3::RotationX(float radians) {
	float sin = std::sin(radians);
	float cos = std::cos(radians);
	return gfm::math::Matrix3x3
	(
		Vector3D(1, 0, 0),
		Vector3D(0, -cos, sin),
		Vector3D(0, sin, cos)
	);
}

gfm::math::Matrix3x3 gfm::math::Matrix3x3::RotationY(float radians) {
	float sin = std::sin(radians);
	float cos = std::cos(radians);
	return gfm::math::Matrix3x3
	(
		Vector3D(-cos, sin, 0),
		Vector3D(0, 1, 0),
		Vector3D(sin, cos)
	);
}

gfm::math::Matrix3x3 gfm::math::Matrix3x3::RotationZ(float radians) {
	float sin = std::sin(radians);
	float cos = std::cos(radians);
	return gfm::math::Matrix3x3
	(
		Vector3D(-cos, sin, 0),
		Vector3D(sin, cos, 0),
		Vector3D(0, 0, 1)
	);
}

gfm::math::Matrix3x3 gfm::math::Matrix3x3::Orthographic(SkalarType left, SkalarType right, SkalarType bottom, SkalarType top) {
	auto result = Identity();
	SkalarType x = -(2.0f / (right - left));
	SkalarType y = (2.0f / (top - bottom));
	using namespace INTERNAL::gpu;
	if(Context::Instance().GetAPI() != GraphicAPI::eOPENGL) {
		y = -y;
	}
	result[0][0] = x;
	result[1][1] = y;
	result[2][2] = -1.0f;
	return result;
}

gfm::math::Matrix3x3 gfm::math::Matrix3x3::Translate(const Vector3D& vec) {
	return {
		1.0f, 0.0f, vec.x,
		0.0f, 1.0f, vec.y,
		0.0f, 0.0f, vec.z
	};
}

gfm::math::Matrix3x3 gfm::math::Matrix3x3::Scale(const Vector3D& vec) {
	return {
		vec.x, 0.0f, 0.0f,
		0.0f, vec.y, 0.0f,
		0.0f, 0.0f, vec.z
	};
}

gfm::math::Matrix3x3 gfm::math::Matrix3x3::Transpose(const Matrix3x3& mat) {
	return {
		{mat.colums[0].x, mat.colums[1].x, mat.colums[2].x},
		{mat.colums[0].y, mat.colums[1].y, mat.colums[2].y},
		{mat.colums[0].z, mat.colums[1].z, mat.colums[2].z}
	};

}

gfm::math::Matrix3x3 gfm::math::Matrix3x3::Identity() {
	return {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
}

void gfm::math::Matrix3x3::ToIdentity() {
	std::memset(colums, 0, sizeof(gfm::math::Matrix3x3));
	colums[0].x = 1.0f;
	colums[1].y = 1.0f;
	colums[2].z = 1.0f;
}

const typename gfm::math::Matrix3x3::ColumType& gfm::math::Matrix3x3::operator[](size_t index) const {
	if(index < 0 || index > 2) {
		throw  std::out_of_range("Matrix3x3 operator[] index out of Range!");
		return colums[0]; // warning fix
	}
	return colums[index];
}

typename gfm::math::Matrix3x3::ColumType& gfm::math::Matrix3x3::operator[](size_t index) {
	if(index < 0 || index > 2) {
		throw  std::out_of_range("Matrix3x3 operator[] index out of Range!");
		return colums[0]; // warning fix
	}
	return colums[index];
}

typename gfm::math::Matrix3x3::ColumType gfm::math::Matrix3x3::row(size_t index) const {
	return this->operator[](index);
}

typename gfm::math::Matrix3x3::ColumType gfm::math::Matrix3x3::col(size_t index) const {
	return {this->operator[](0)[index], this->operator[](1)[index], this->operator[](2)[index]};
}

gfm::math::Matrix3x3& gfm::math::Matrix3x3::operator += (const gfm::math::Matrix3x3& other) {
	colums[0] += other.colums[0];
	colums[1] += other.colums[1];
	colums[2] += other.colums[2];
	return *this;
}

gfm::math::Matrix3x3& gfm::math::Matrix3x3::operator += (SkalarType skalar) {
	colums[0] += skalar;
	colums[1] += skalar;
	colums[2] += skalar;
	return *this;
}

gfm::math::Matrix3x3& gfm::math::Matrix3x3::operator -= (const gfm::math::Matrix3x3& other) {
	colums[0] -= other.colums[0];
	colums[1] -= other.colums[1];
	colums[2] -= other.colums[2];
	return *this;
}

gfm::math::Matrix3x3& gfm::math::Matrix3x3::operator -= (SkalarType skalar) {
	colums[0] -= skalar;
	colums[1] -= skalar;
	colums[2] -= skalar;
	return *this;
}

gfm::math::Matrix3x3& gfm::math::Matrix3x3::operator *= (const gfm::math::Matrix3x3& other) {

	gfm::math::Matrix3x3 mat(
		colums[0][0] * other.colums[0][0] + colums[1][0] * other.colums[0][1] + colums[2][0] * other.colums[0][2],
		colums[0][1] * other.colums[0][0] + colums[1][1] * other.colums[0][1] + colums[2][1] * other.colums[0][2],
		colums[0][2] * other.colums[0][0] + colums[1][2] * other.colums[0][1] + colums[2][2] * other.colums[0][2],

		colums[0][0] * other.colums[1][0] + colums[1][0] * other.colums[1][1] + colums[2][0] * other.colums[1][2],
		colums[0][1] * other.colums[1][0] + colums[1][1] * other.colums[1][1] + colums[2][1] * other.colums[1][2],
		colums[0][2] * other.colums[1][0] + colums[1][2] * other.colums[1][1] + colums[2][2] * other.colums[1][2],

		colums[0][0] * other.colums[2][0] + colums[1][0] * other.colums[2][1] + colums[2][0] * other.colums[2][2],
		colums[0][1] * other.colums[2][0] + colums[1][1] * other.colums[2][1] + colums[2][1] * other.colums[2][2],
		colums[0][2] * other.colums[2][0] + colums[1][2] * other.colums[2][1] + colums[2][2] * other.colums[2][2]
	);
	return *this = mat;

}

gfm::math::Matrix3x3& gfm::math::Matrix3x3::operator *= (SkalarType skalar) {
	colums[0] *= skalar;
	colums[1] *= skalar;
	colums[2] *= skalar;
	return *this;
}

gfm::math::Matrix3x3& gfm::math::Matrix3x3::operator /= (const gfm::math::Matrix3x3 & other) {
	GFM_DEBUG_ASSERT(false, GFM_STRING("MATRIX MATRIX DIVISION IS NOT IMPLEMENTED YET!"));
	return *this; // warning fix
}

gfm::math::Matrix3x3& gfm::math::Matrix3x3::operator /= (SkalarType skalar) {
	colums[0] /= skalar;
	colums[1] /= skalar;
	colums[2] /= skalar;
	return *this;
}

gfm::math::Matrix3x3& gfm::math::Matrix3x3::operator ++() {
	++colums[0];
	++colums[1];
	++colums[2];
	return *this;
}

gfm::math::Matrix3x3& gfm::math::Matrix3x3::operator --() {
	--colums[0];
	--colums[1];
	--colums[2];
	return *this;
}

gfm::math::Matrix3x3 gfm::math::Matrix3x3::operator ++(int) {
	gfm::math::Matrix3x3 temp(*this);
	++*this;
	return temp;
}

gfm::math::Matrix3x3 gfm::math::Matrix3x3::operator --(int) {
	gfm::math::Matrix3x3 temp(*this);
	--*this;
	return temp;
}

gfm::math::Matrix3x3 gfm::math::operator +(const gfm::math::Matrix3x3 & mat) {
	return mat;
}

gfm::math::Matrix3x3 gfm::math::operator +(const gfm::math::Matrix3x3& left, const gfm::math::Matrix3x3& right) {
	return gfm::math::Matrix3x3(
		left[0] + right[0],
		left[1] + right[1],
		left[2] + right[2]
	);
}

gfm::math::Matrix3x3 gfm::math::operator +(const gfm::math::Matrix3x3& left, gfm::math::Matrix3x3::SkalarType skalar) {
	return gfm::math::Matrix3x3(
		left[0] + skalar,
		left[1] + skalar,
		left[2] + skalar
		);
}

gfm::math::Matrix3x3 gfm::math::operator +(gfm::math::Matrix3x3::SkalarType skalar, const gfm::math::Matrix3x3& right) {
	return gfm::math::Matrix3x3(
		skalar + right[0],
		skalar + right[1],
		skalar + right[2]
	);
}

gfm::math::Matrix3x3 gfm::math::operator -(const gfm::math::Matrix3x3& mat) {
	gfm::math::Matrix3x3 temp(-mat.col(0), -mat.col(1), -mat.col(2));
	return temp;
}

gfm::math::Matrix3x3 gfm::math::operator -(const gfm::math::Matrix3x3& left, const gfm::math::Matrix3x3& right) {
	return gfm::math::Matrix3x3(
		left[0] - right[0],
		left[1] - right[1],
		left[2] - right[2]
		);
}

gfm::math::Matrix3x3 gfm::math::operator -(const gfm::math::Matrix3x3& left, gfm::math::Matrix3x3::SkalarType skalar) {
	return gfm::math::Matrix3x3(
		left[0] - skalar,
		left[1] - skalar,
		left[2] - skalar
		);
}

gfm::math::Matrix3x3 gfm::math::operator -(gfm::math::Matrix3x3::SkalarType skalar, const gfm::math::Matrix3x3& right) {
	return gfm::math::Matrix3x3(
		skalar - right[0],
		skalar - right[1],
		skalar - right[2]
		);
}

gfm::math::Matrix3x3 gfm::math::operator * (const gfm::math::Matrix3x3& left, const gfm::math::Matrix3x3& right) {
	gfm::math::Matrix3x3 temp(left);
	return (temp *= right);
}

gfm::math::Matrix3x3 gfm::math::operator * (const gfm::math::Matrix3x3& left, gfm::math::Matrix3x3::SkalarType skalar) {
	return gfm::math::Matrix3x3(
		left[0] * skalar,
		left[1] * skalar,
		left[2] * skalar
		);
}

gfm::math::Matrix3x3 gfm::math::operator * (gfm::math::Matrix3x3::SkalarType skalar, const gfm::math::Matrix3x3& right) {
	return gfm::math::Matrix3x3
	(
		right[0] * skalar,
		right[1] * skalar,
		right[2] * skalar
	);
}

typename gfm::math::Matrix3x3::ColumType gfm::math::operator * (const gfm::math::Matrix3x3& left, const typename gfm::math::Matrix3x3::ColumType& vec) {
	return typename gfm::math::Matrix3x3::ColumType
	(
		left[0][0] * vec.x + left[1][0] * vec.y + left[2][0] * vec.z,
		left[0][1] * vec.x + left[1][1] * vec.y + left[2][1] * vec.z,
		left[0][2] * vec.x + left[1][2] * vec.y + left[2][2] * vec.z
	);
}

typename gfm::math::Matrix3x3::ColumType gfm::math::operator * (const typename gfm::math::Matrix3x3::ColumType& vec, const gfm::math::Matrix3x3 & right) {
	return typename gfm::math::Matrix3x3::ColumType
	(
		vec.x * right[0][0] + vec.y * right[0][1] + vec.z * right[0][2],
		vec.x * right[1][0] + vec.y * right[1][1] + vec.z * right[1][2],
		vec.x * right[2][0] + vec.y * right[2][1] + vec.z * right[1][2]
	);
}

gfm::math::Matrix3x3 gfm::math::operator / (const gfm::math::Matrix3x3& left, const gfm::math::Matrix3x3& right) {
	gfm::math::Matrix3x3 temp(left);
	return (temp /= right);
}

gfm::math::Matrix3x3 gfm::math::operator / (const gfm::math::Matrix3x3 & left, gfm::math::Matrix3x3::SkalarType skalar) {
	return gfm::math::Matrix3x3
	(
		left[0] / skalar,
		left[1] / skalar,
		left[2] / skalar
	);
}

gfm::math::Matrix3x3 gfm::math::operator / (gfm::math::Matrix3x3::SkalarType skalar, const gfm::math::Matrix3x3 & right) {
	return gfm::math::Matrix3x3
	(
		right[0] / skalar,
		right[1] / skalar,
		right[2] / skalar
	);
}

typename gfm::math::Matrix3x3::ColumType gfm::math::operator / (const gfm::math::Matrix3x3 & left, const typename gfm::math::Matrix3x3::ColumType & vec) {
	return typename gfm::math::Matrix3x3::ColumType
	(
		left[0][0] / vec.x + left[1][0] / vec.y + left[2][0] / vec.z,
		left[0][1] / vec.x + left[1][1] / vec.y + left[2][1] / vec.z,
		left[0][2] / vec.x + left[1][2] / vec.y + left[2][2] / vec.z
	);
}

typename gfm::math::Matrix3x3::ColumType gfm::math::operator / (const typename gfm::math::Matrix3x3::ColumType & vec, const gfm::math::Matrix3x3 & right) {
	return typename gfm::math::Matrix3x3::ColumType
	(
		vec.x / right[0][0] + vec.y / right[0][1] + vec.z / right[0][2],
		vec.x / right[1][0] + vec.y / right[1][1] + vec.z / right[1][2],
		vec.x / right[2][0] + vec.y / right[2][1] + vec.z / right[2][2]
	);
}
#pragma warning(pop)

