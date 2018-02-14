#pragma once
#include <utility>
#include <stdexcept>
#include "Matrix4x4.h"
#include "..\Macro\Assertions.h"
#include "Convertions.h"


gfm::math::Matrix4x4::Matrix4x4(
	SkalarType first,     SkalarType second,  SkalarType  third,   SkalarType fourth,
	SkalarType fifth,     SkalarType sixth,   SkalarType  seventh, SkalarType eight,
	SkalarType nineth,    SkalarType ten,     SkalarType  eleven,  SkalarType twelve,
	SkalarType thirtheen, SkalarType forteen, SkalarType fiftheen, SkalarType sixteen) {
	colums[0][0] = first;
	colums[0][1] = second;
	colums[0][2] = third;
	colums[0][3] = fourth;
	colums[1][0] = fifth;
	colums[1][1] = sixth;
	colums[1][2] = seventh;
	colums[1][3] = eight;
	colums[2][0] = nineth;
	colums[2][1] = ten;
	colums[2][2] = eleven;
	colums[2][3] = twelve;
	colums[3][0] = thirtheen;
	colums[3][1] = forteen;
	colums[3][2] = fiftheen;
	colums[3][3] = sixteen;
}

gfm::math::Matrix4x4 gfm::math::Matrix4x4::Perspective(SkalarType fov, SkalarType aspectRatio, SkalarType near, SkalarType far) {
	auto tanHalfFov = std::tan(fov / 2.0f);
	Matrix4x4 res;
	res[0][0] = 1 / (aspectRatio * tanHalfFov);
	res[1][1] = 1 / (tanHalfFov);
	res[2][2] = -(far + near) / (far - near);
	res[2][3] = -1.0f;
	res[3][2] = -(2.0f * far * near) / (far - near);
	return res;
}

gfm::math::Matrix4x4 gfm::math::Matrix4x4::Rotation(float radians, const Vec3& axis) {
	auto c = std::cos(radians);
	auto s = std::sin(radians);
	Vec3 normalizedAxis = axis.Normalize();
	Vector3D temp((1.0f - c) * axis.x, (1.0f - c) * axis.y, (1.0f - c) * axis.z);
	Matrix4x4 rotation = Matrix4x4::Identity();
	rotation[0][0] = c + temp[0] * normalizedAxis[0];
	rotation[0][1] = 0 + temp[0] * normalizedAxis[1] + s * normalizedAxis[2];
	rotation[0][2] = 0 + temp[0] * normalizedAxis[2] - s * normalizedAxis[1];
	rotation[1][0] = 0 + temp[1] * normalizedAxis[0] - s * normalizedAxis[2];
	rotation[1][1] = c + temp[1] * normalizedAxis[1];
	rotation[1][2] = 0 + temp[1] * normalizedAxis[2] + s * axis[0];
	rotation[2][0] = 0 + temp[2] * normalizedAxis[0] + s * axis[1];
	rotation[2][1] = 0 + temp[2] * normalizedAxis[1] - s * axis[0];
	rotation[2][2] = c + temp[2] * normalizedAxis[2];
	return rotation;
}


gfm::math::Matrix4x4 gfm::math::Matrix4x4::Orthographic(SkalarType left, SkalarType right, SkalarType bottom, SkalarType top) {
	auto result = Identity();
	result[0][0] = 2.0f / (right - left);
	result[1][1] = 2.0f / (top - bottom);
	result[2][2] = -1.0f;
	result[3][0] = -(right + left) / (right - left);
	result[3][1] = -(top + bottom) / (top - bottom);
	return result;
}

gfm::math::Matrix4x4 gfm::math::Matrix4x4::Translate(const Vector3D& translate) {
	return {
		 1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 1.0f, 0.0f,
	     translate.x, translate.y, translate.z, 1.0f
	};
}

gfm::math::Matrix4x4 gfm::math::Matrix4x4::Scale(const Vector3D& scale) {
	return {
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f,    1.0f
	};
}

gfm::math::Matrix4x4 gfm::math::Matrix4x4::Transpose(const Matrix4x4& mat) {
	return {
		mat.colums[0].x, mat.colums[1].x, mat.colums[2].x, mat.colums[3].x,
		mat.colums[0].y, mat.colums[1].y, mat.colums[2].y, mat.colums[3].y,
		mat.colums[0].z, mat.colums[1].z, mat.colums[2].z, mat.colums[3].z,
		mat.colums[0].w, mat.colums[1].w, mat.colums[2].w, mat.colums[3].w
	};
}

gfm::math::Matrix4x4 gfm::math::Matrix4x4::Identity() {
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

gfm::math::Matrix4x4 gfm::math::Matrix4x4::Orthographic(SkalarType left, SkalarType right, SkalarType bottom, SkalarType top, SkalarType near, SkalarType far) {
	auto result = Identity();
	result.elements[0 + 0 * 4] = 2.0f / (right - left);
	result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result.elements[2 + 2 * 4] = 2.0f / (near - far);
	result.elements[3 + 0 * 4] = (left + right) / (left - right);
	result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
	result.elements[3 + 2 * 4] = (far + near) / (far - near);
	return result;
}

gfm::math::Matrix4x4::Matrix4x4(
	SkalarType first, SkalarType second, SkalarType third, SkalarType fourth,
	SkalarType fifth, SkalarType sixth, SkalarType seven, SkalarType eight,
	SkalarType nine, SkalarType ten, SkalarType eleven, SkalarType twelve,
	const Vector4D& vec_fourth) {
	colums[0][0] = first;
	colums[0][1] = second;
	colums[0][2] = third;
	colums[0][3] = fourth;
	colums[1][0] = fifth;
	colums[1][1] = sixth;
	colums[1][2] = seven;
	colums[1][3] = eight;
	colums[2][0] = nine;
	colums[2][1] = ten;
	colums[2][2] = eleven;
	colums[2][3] = twelve;
	colums[3] = vec_fourth;
}

gfm::math::Matrix4x4::Matrix4x4(
	SkalarType first, SkalarType second, SkalarType third, SkalarType fourth,
	SkalarType fifth, SkalarType sixth, SkalarType seventh, SkalarType eigth,
	const Vector4D& vec_second, const Vector4D& vec_third) {
	colums[0][0] = first;
	colums[0][1] = second;
	colums[0][2] = third;
	colums[0][3] = fourth;
	colums[1][0] = fifth;
	colums[1][1] = sixth;
	colums[1][2] = seventh;
	colums[1][3] = eigth;
	colums[1] = vec_second;
	colums[2] = vec_third;
}

gfm::math::Matrix4x4::Matrix4x4(
	SkalarType first, SkalarType second, SkalarType third, SkalarType fourth,
	const Vector4D& vec_first, const Vector4D& vec_second, const Vector4D& vec_third) {
	colums[0][0] = first;
	colums[0][1] = second;
	colums[0][2] = third;
	colums[0][3] = fourth;
	colums[1] = vec_first;
	colums[2] = vec_second;
	colums[2] = vec_third;
}

gfm::math::Matrix4x4::Matrix4x4(
	const Vector4D& vec_first, const Vector4D& vec_second, const Vector4D& vec_third,
	SkalarType first, SkalarType second, SkalarType third, SkalarType fourth) {
	colums[0] = vec_first;
	colums[1] = vec_second;
	colums[2] = vec_third;
	colums[3][0] = first;
	colums[3][1] = second;
	colums[3][0] = third;
	colums[3][1] = fourth;
}

gfm::math::Matrix4x4::Matrix4x4(
	const Vector4D& vec_first, const Vector4D& vec_second,
	SkalarType first, SkalarType second, SkalarType third, SkalarType fourth,
	SkalarType fifth, SkalarType sixth, SkalarType seventh, SkalarType eight) {
	colums[0] = vec_first;
	colums[1] = vec_second;
	colums[2][0] = first;
	colums[2][1] = second;
	colums[2][0] = third;
	colums[2][1] = fourth;
	colums[3][0] = fifth;
	colums[3][1] = sixth;
	colums[3][0] = seventh;
	colums[3][1] = eight;
}

gfm::math::Matrix4x4::Matrix4x4(
	const Vector4D& vec_first, SkalarType first, SkalarType second, SkalarType third, SkalarType fourth,
	SkalarType fifth, SkalarType sixth, SkalarType seven, SkalarType eight,
	SkalarType nineth, SkalarType ten, SkalarType eleven, SkalarType twelve) {
	colums[0] = vec_first;
	colums[1][0] = first;
	colums[1][1] = second;
	colums[1][0] = third;
	colums[1][1] = fourth;
	colums[2][0] = fifth;
	colums[2][1] = sixth;
	colums[2][0] = seven;
	colums[2][1] = eight;
	colums[3][0] = nineth;
	colums[3][1] = ten;
	colums[3][0] = eleven;
	colums[3][1] = twelve;
}

gfm::math::Matrix4x4::Matrix4x4(const Vector4D& vec_first, const Vector4D& vec_second, const Vector4D& vec_third, const Vector4D& vec_fourth) {
	colums[0] = vec_first;
	colums[1] = vec_second;
	colums[2] = vec_third;
	colums[3] = vec_fourth;
}

void gfm::math::Matrix4x4::ToIdentity() {
	std::memset(colums, 0, sizeof(ColumType) * 16);
	colums[0].x = 1.0f;
	colums[1].y = 1.0f;
	colums[2].z = 1.0f;
	colums[3].w = 1.0f;
}

const typename gfm::math::Matrix4x4::ColumType& gfm::math::Matrix4x4::operator [](size_t index) const {
	if(index < 0 || index > 3) {
		throw  std::out_of_range("Matrix4x4 operator[] index out of Range!");
		return colums[0]; // warning fix
	}
	return colums[index];
}

typename gfm::math::Matrix4x4::ColumType& gfm::math::Matrix4x4::operator[](size_t index) {
	if(index < 0 || index > 3) {
		throw  std::range_error("Matrix4x4 operator[] index out of Range!");
		return colums[0]; // warning fix
	}
	return colums[index];
}

const typename gfm::math::Matrix4x4::ColumType& gfm::math::Matrix4x4::Row(size_t index) const {
	return this->operator[](index);
}

const typename gfm::math::Matrix4x4::ColumType gfm::math::Matrix4x4::Col(size_t index) const {
	return {this->operator[](0)[index], this->operator[](1)[index], this->operator[](2)[index], this->operator[](3)[index]};
}

gfm::math::Matrix4x4& gfm::math::Matrix4x4::operator += (const gfm::math::Matrix4x4& other) {
	colums[0] += other.colums[0];
	colums[1] += other.colums[1];
	colums[2] += other.colums[2];
	colums[3] += other.colums[3];
	return *this;
}

gfm::math::Matrix4x4& gfm::math::Matrix4x4::operator += (SkalarType skalar) {
	colums[0] += skalar;
	colums[1] += skalar;
	colums[2] += skalar;
	colums[3] += skalar;
	return *this;
}

gfm::math::Matrix4x4& gfm::math::Matrix4x4::operator -= (const gfm::math::Matrix4x4& other) {
	colums[0] -= other.colums[0];
	colums[1] -= other.colums[1];
	colums[2] -= other.colums[2];
	colums[3] -= other.colums[3];
	return *this;
}

gfm::math::Matrix4x4& gfm::math::Matrix4x4::operator -= (SkalarType skalar) {
	colums[0] -= skalar;
	colums[1] -= skalar;
	colums[2] -= skalar;
	colums[3] -= skalar;
	return *this;
}

gfm::math::Matrix4x4& gfm::math::Matrix4x4::operator *= (const gfm::math::Matrix4x4& other) {

	Matrix4x4 mat(
		colums[0][0] * other.colums[0][0] + colums[1][0] * other.colums[0][1] + colums[2][0] * other.colums[0][2] + colums[3][0] * other.colums[0][3],
		colums[0][1] * other.colums[0][0] + colums[1][1] * other.colums[0][1] + colums[2][1] * other.colums[0][2] + colums[3][1] * other.colums[0][3],
		colums[0][2] * other.colums[0][0] + colums[1][2] * other.colums[0][1] + colums[2][2] * other.colums[0][2] + colums[3][2] * other.colums[0][3],
		colums[0][3] * other.colums[0][0] + colums[1][3] * other.colums[0][1] + colums[2][3] * other.colums[0][2] + colums[3][3] * other.colums[0][3],

		colums[0][0] * other.colums[1][0] + colums[1][0] * other.colums[1][1] + colums[2][0] * other.colums[1][2] + colums[3][0] * other.colums[1][3],
		colums[0][1] * other.colums[1][0] + colums[1][1] * other.colums[1][1] + colums[2][1] * other.colums[1][2] + colums[3][1] * other.colums[1][3],
		colums[0][2] * other.colums[1][0] + colums[1][2] * other.colums[1][1] + colums[2][2] * other.colums[1][2] + colums[3][2] * other.colums[1][3],
		colums[0][3] * other.colums[1][0] + colums[1][3] * other.colums[1][1] + colums[2][3] * other.colums[1][2] + colums[3][3] * other.colums[1][3],

		colums[0][0] * other.colums[2][0] + colums[1][0] * other.colums[2][1] + colums[2][0] * other.colums[2][2] + colums[3][0] * other.colums[2][3],
		colums[0][1] * other.colums[2][0] + colums[1][1] * other.colums[2][1] + colums[2][1] * other.colums[2][2] + colums[3][1] * other.colums[2][3],
		colums[0][2] * other.colums[2][0] + colums[1][2] * other.colums[2][1] + colums[2][2] * other.colums[2][2] + colums[3][2] * other.colums[2][3],
		colums[0][3] * other.colums[2][0] + colums[1][3] * other.colums[2][1] + colums[2][3] * other.colums[2][2] + colums[3][3] * other.colums[2][3],

		colums[0][0] * other.colums[3][0] + colums[1][0] * other.colums[3][1] + colums[2][0] * other.colums[3][2] + colums[3][0] * other.colums[3][3],
		colums[0][1] * other.colums[3][0] + colums[1][1] * other.colums[3][1] + colums[2][1] * other.colums[3][2] + colums[3][1] * other.colums[3][3],
		colums[0][2] * other.colums[3][0] + colums[1][2] * other.colums[3][1] + colums[2][2] * other.colums[3][2] + colums[3][2] * other.colums[3][3],
		colums[0][3] * other.colums[3][0] + colums[1][3] * other.colums[3][1] + colums[2][3] * other.colums[3][2] + colums[3][3] * other.colums[3][3]
	);

	return *this = mat;

}

gfm::math::Matrix4x4& gfm::math::Matrix4x4::operator *= (SkalarType skalar) {
	colums[0] *= skalar;
	colums[1] *= skalar;
	colums[2] *= skalar;
	colums[3] *= skalar;
	return *this;
}

gfm::math::Matrix4x4& gfm::math::Matrix4x4::operator /= (const gfm::math::Matrix4x4 & other) {
	GFM_DEBUG_ASSERT(false, GFM_STRING("MATRIX MATRIX DIVISION IS NOT IMPLEMENTED YET!"));
	return *this; // warning fix
}

gfm::math::Matrix4x4& gfm::math::Matrix4x4::operator /= (SkalarType skalar) {
	colums[0] /= skalar;
	colums[1] /= skalar;
	colums[2] /= skalar;
	colums[3] /= skalar;
	return *this;
}

gfm::math::Matrix4x4& gfm::math::Matrix4x4::operator ++() {
	++colums[0];
	++colums[1];
	++colums[2];
	++colums[3];
	return *this;
}

gfm::math::Matrix4x4& gfm::math::Matrix4x4::operator --() {
	--colums[0];
	--colums[1];
	--colums[2];
	--colums[3];
	return *this;
}

gfm::math::Matrix4x4 gfm::math::Matrix4x4::operator ++(int) {
	Matrix4x4 temp(*this);
	++*this;
	return temp;
}

gfm::math::Matrix4x4 gfm::math::Matrix4x4::operator --(int) {
	Matrix4x4 temp(*this);
	--*this;
	return temp;
}

gfm::math::Matrix4x4 gfm::math::operator +(const gfm::math::Matrix4x4 & mat) {
	return mat;
}
gfm::math::Matrix4x4 gfm::math::operator +(const gfm::math::Matrix4x4& left, const gfm::math::Matrix4x4& right) {
	return gfm::math::Matrix4x4(
		left[0] + right[0],
		left[1] + right[1],
		left[2] + right[2],
		left[3] + right[3]
	);
}

gfm::math::Matrix4x4 gfm::math::operator +(const gfm::math::Matrix4x4& left, gfm::math::Matrix4x4::SkalarType skalar) {
	return gfm::math::Matrix4x4(
		left[0] + skalar,
		left[1] + skalar,
		left[2] + skalar,
		left[3] + skalar
	);
}

gfm::math::Matrix4x4 gfm::math::operator +(gfm::math::Matrix4x4::SkalarType  skalar, const gfm::math::Matrix4x4& right) {
	return gfm::math::Matrix4x4(
		skalar + right[0],
		skalar + right[1],
		skalar + right[2],
		skalar + right[3]
	);
}

gfm::math::Matrix4x4 gfm::math::operator -(const gfm::math::Matrix4x4& mat) {
	gfm::math::Matrix4x4 temp(-mat.Col(0), -mat.Col(1), -mat.Col(2), -mat.Col(3));
	return temp;
}

gfm::math::Matrix4x4 gfm::math::operator -(const gfm::math::Matrix4x4& left, const gfm::math::Matrix4x4& right) {
	return gfm::math::Matrix4x4(
		left[0] - right[0],
		left[1] - right[1],
		left[2] - right[2],
		left[3] - right[3]
	);
}

gfm::math::Matrix4x4 gfm::math::operator -(const gfm::math::Matrix4x4& left, gfm::math::Matrix4x4::SkalarType  skalar) {
	return gfm::math::Matrix4x4(
		left[0] - skalar,
		left[1] - skalar,
		left[2] - skalar,
		left[3] - skalar
	);
}

gfm::math::Matrix4x4 gfm::math::operator -(gfm::math::Matrix4x4::SkalarType  skalar, const gfm::math::Matrix4x4& right) {
	return gfm::math::Matrix4x4(
		skalar - right[0],
		skalar - right[1],
		skalar - right[2],
		skalar - right[3]
	);
}

gfm::math::Matrix4x4 gfm::math::operator * (const gfm::math::Matrix4x4& left, const gfm::math::Matrix4x4& right) {
	gfm::math::Matrix4x4 temp(left);
	return (temp *= right);
}

gfm::math::Matrix4x4 gfm::math::operator * (const gfm::math::Matrix4x4& left, gfm::math::Matrix4x4::SkalarType  skalar) {
	return gfm::math::Matrix4x4(
		left[0] * skalar,
		left[1] * skalar,
		left[2] * skalar,
		left[3] * skalar
	);
}

gfm::math::Matrix4x4 gfm::math::operator * (gfm::math::Matrix4x4::SkalarType  skalar, const gfm::math::Matrix4x4& right) {
	return gfm::math::Matrix4x4(
		right[0] * skalar,
		right[1] * skalar,
		right[2] * skalar,
		right[3] * skalar
	);
}

typename gfm::math::Matrix4x4::ColumType gfm::math::operator * (const gfm::math::Matrix4x4& left, const typename gfm::math::Matrix4x4::ColumType & vec) {
	return typename gfm::math::Matrix4x4::ColumType(
		left[0][0] * vec.x + left[1][0] * vec.y + left[2][0] * vec.z + left[3][0] * vec.w,
		left[0][1] * vec.x + left[1][1] * vec.y + left[2][1] * vec.z + left[3][1] * vec.w,
		left[0][2] * vec.x + left[1][2] * vec.y + left[2][2] * vec.z + left[3][2] * vec.w,
		left[0][3] * vec.x + left[1][3] * vec.y + left[2][3] * vec.z + left[3][3] * vec.w
	);
}

typename gfm::math::Matrix4x4::ColumType gfm::math::operator * (const typename gfm::math::Matrix4x4::ColumType & vec, const gfm::math::Matrix4x4& right) {
	return typename gfm::math::Matrix4x4::ColumType(
		vec.x * right[0][0] + vec.y * right[0][1] + vec.z * right[0][2] + vec.w * right[0][3],
		vec.x * right[1][0] + vec.y * right[1][1] + vec.z * right[1][2] + vec.w * right[1][3],
		vec.x * right[2][0] + vec.y * right[2][1] + vec.z * right[2][2] + vec.w * right[2][3],
		vec.x * right[3][0] + vec.y * right[3][1] + vec.z * right[3][2] + vec.w * right[3][3]
	);
}

gfm::math::Matrix4x4 gfm::math::operator / (const gfm::math::Matrix4x4& left, const gfm::math::Matrix4x4& right) {
	gfm::math::Matrix4x4 temp(left);
	return (temp /= right);
}

gfm::math::Matrix4x4 gfm::math::operator / (const gfm::math::Matrix4x4& left, gfm::math::Matrix4x4::SkalarType  skalar) {
	return gfm::math::Matrix4x4(
		left[0] / skalar,
		left[1] / skalar,
		left[2] / skalar,
		left[3] / skalar
	);
}

gfm::math::Matrix4x4 gfm::math::operator / (gfm::math::Matrix4x4::SkalarType skalar, const gfm::math::Matrix4x4& right) {
	return gfm::math::Matrix4x4(
		right[0] / skalar,
		right[1] / skalar,
		right[2] / skalar,
		right[3] / skalar
	);
}

typename gfm::math::Matrix4x4::ColumType gfm::math::operator / (const gfm::math::Matrix4x4& left, const typename gfm::math::Matrix4x4::ColumType & vec) {
	return typename gfm::math::Matrix4x4::ColumType(
		left[0][0] / vec.x + left[1][0] / vec.y + left[2][0] / vec.z + left[3][0] / vec.w,
		left[0][1] / vec.x + left[1][1] / vec.y + left[2][1] / vec.z + left[3][1] / vec.w,
		left[0][2] / vec.x + left[1][2] / vec.y + left[2][2] / vec.z + left[3][2] / vec.w,
		left[0][3] / vec.x + left[1][3] / vec.y + left[2][3] / vec.z + left[3][3] / vec.w
	);
}

typename gfm::math::Matrix4x4::ColumType gfm::math::operator / (const typename gfm::math::Matrix4x4::ColumType & vec, const gfm::math::Matrix4x4& right) {
	return typename gfm::math::Matrix4x4::ColumType(
		vec.x / right[0][0] + vec.y / right[0][1] + vec.z / right[0][2] + vec.w / right[0][3],
		vec.x / right[1][0] + vec.y / right[1][1] + vec.z / right[1][2] + vec.w / right[1][3],
		vec.x / right[2][0] + vec.y / right[2][1] + vec.z / right[2][2] + vec.w / right[2][3],
		vec.x / right[3][0] + vec.y / right[3][1] + vec.z / right[3][2] + vec.w / right[3][3]
	);
}


