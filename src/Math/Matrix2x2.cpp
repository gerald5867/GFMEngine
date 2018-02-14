#pragma once
#include <utility>
#include <stdexcept>
#include "Matrix2x2.h"
#include "..\Macro\Assertions.h"
#include "Convertions.h"
#include "..\GPUApi\Context.h"

gfm::math::Matrix2x2::Matrix2x2(SkalarType first, SkalarType second, SkalarType third, SkalarType fourth) {
	colums[0].x = first; colums[0].y = second;
	colums[1].x = third; colums[1].y = fourth;
}

gfm::math::Matrix2x2::Matrix2x2(SkalarType first, SkalarType second, SkalarType third) {
	colums[0].x = first; colums[0].y = second;
	colums[1].x = third; colums[1].y = 0;
}

gfm::math::Matrix2x2::Matrix2x2(SkalarType first, SkalarType second) {
	colums[0].x = first; colums[0].y = second;
	colums[1].x = 0;     colums[1].y = 0;
}

gfm::math::Matrix2x2::Matrix2x2(SkalarType first) {
	colums[0].x = first; colums[0].y = first;
	colums[1].x = first; colums[1].y = first;
}

gfm::math::Matrix2x2::Matrix2x2(const Vector2D & first, const Vector2D & second) {
	colums[0] = first;
	colums[1] = second;
}

gfm::math::Matrix2x2::Matrix2x2(const Vector2D & left, SkalarType first, SkalarType second) {
	colums[0] = left;
	colums[1].x = first; colums[1].y = second;
}

gfm::math::Matrix2x2::Matrix2x2(SkalarType first, const Vector2D& middle, SkalarType second) {
	colums[0].x = first;      colums[0].y = middle.x;
	colums[1].x = middle.y; colums[1].y = second;
}

gfm::math::Matrix2x2::Matrix2x2(SkalarType first, SkalarType second, const Vector2D& right) {
	colums[0].x = first;  colums[0].y = second;
	colums[1] = right;
}

gfm::math::Matrix2x2::Matrix2x2(SkalarType skalar, const Vector3D& right) {
	colums[0].x = skalar;  colums[0].y = right.x;
	colums[1] = right.yz();
}

gfm::math::Matrix2x2::Matrix2x2(const Vector3D& left, SkalarType skalar) {
	colums[0] = left.xy();
	colums[1].x = left.z, colums[1].y = skalar;
}

gfm::math::Matrix2x2::Matrix2x2(const Vector4D& vec) {
	colums[0] = vec.xy();
	colums[1] = vec.zw();
}

void gfm::math::Matrix2x2::ToIdentity() {
	std::memset(colums, 0, sizeof(SkalarType) * 4);
	colums[0].x = 1.0f;
	colums[1].y = 1.0f;
}

gfm::math::Matrix2x2 gfm::math::Matrix2x2::Rotation(SkalarType radians, bool clock_wise) noexcept {
	SkalarType sin = std::sin(radians);
	SkalarType cos = std::cos(radians);
	return gfm::math::Matrix2x2
	(
		Vector2D(cos, (clock_wise) ? -sin : sin),
		Vector2D((clock_wise) ? sin : -sin, cos)
	);
}

gfm::math::Matrix2x2 gfm::math::Matrix2x2::Orthographic(SkalarType left, SkalarType right, SkalarType bottom, SkalarType top) {
	SkalarType x = -(2.0f / (right - left));
	SkalarType y = (2.0f / (top - bottom));
	using namespace INTERNAL::gpu;
	if(Context::Instance().GetAPI() != GraphicAPI::eOPENGL) {
		y = -y;
	}
	return {
		x, 0.0f,
		0.0f, y
	};
}


gfm::math::Matrix2x2 gfm::math::Matrix2x2::Translate(const Vector2D& translate) {
	return {
		1.0f, translate.x,
		0.0f, translate.y
	};
}

gfm::math::Matrix2x2 gfm::math::Matrix2x2::Scale(const Vector2D& scale) {
	return {
		scale.x, 0.0f,
		0.0f,   scale.y
	};
}

gfm::math::Matrix2x2 gfm::math::Matrix2x2::Transpose(const Matrix2x2& mat) {
	return {
		{mat.colums[0].x, mat.colums[1].x},
		{mat.colums[0].y, mat.colums[1].y}
	};
}

gfm::math::Matrix2x2 gfm::math::Matrix2x2::Identity() {
	return {
		1.0f, 0.0f, 
		0.0f, 1.0f
	};
}

const typename gfm::math::Matrix2x2::ColumType & gfm::math::Matrix2x2::operator[](size_t index) const {
	if(index < 0 || index > 1) {
		throw std::range_error("Matrix2x2 operator[] index out of Range!");
		return colums[0]; // warning fix
	}
	return colums[index];
}

typename gfm::math::Matrix2x2::ColumType & gfm::math::Matrix2x2::operator[](size_t index) {
	if(index < 0 || index > 1) {
		throw  std::range_error("Matrix2x2 operator[] index out of Range!");
		return colums[0]; // warning fix
	}
	return colums[index];
}

typename gfm::math::Matrix2x2::ColumType gfm::math::Matrix2x2::row(size_t index) const {
	return this->operator[](index);
}

typename gfm::math::Matrix2x2::ColumType gfm::math::Matrix2x2::col(size_t index) const {
	return {this->operator[](0)[index], this->operator[](1)[index]};
}

gfm::math::Matrix2x2& gfm::math::Matrix2x2::operator += (const gfm::math::Matrix2x2 & other) {
	colums[0] += other.colums[0];
	colums[1] += other.colums[1];
	return *this;
}

gfm::math::Matrix2x2& gfm::math::Matrix2x2::operator += (SkalarType skalar) {
	colums[0] += skalar;
	colums[1] += skalar;
	return *this;
}

gfm::math::Matrix2x2& gfm::math::Matrix2x2::operator -= (const gfm::math::Matrix2x2 & other) {
	colums[0] -= other.colums[0];
	colums[1] -= other.colums[1];
	return *this;
}

gfm::math::Matrix2x2& gfm::math::Matrix2x2::operator -= (SkalarType skalar) {
	colums[0] -= skalar;
	colums[1] -= skalar;
	return *this;
}

gfm::math::Matrix2x2& gfm::math::Matrix2x2::operator *= (const gfm::math::Matrix2x2 & other) {

	gfm::math::Matrix2x2 mat(
		colums[0][0] * other[0][0] + colums[1][0] * other[0][1],
		colums[0][1] * other[0][0] + colums[1][1] * other[0][1],
		colums[0][0] * other[1][0] + colums[1][0] * other[1][1],
		colums[0][1] * other[1][0] + colums[1][1] * other[1][1]
	);

	return *this = mat;

}

gfm::math::Matrix2x2& gfm::math::Matrix2x2::operator *= (SkalarType skalar) {
	colums[0] *= skalar;
	colums[1] *= skalar;
	return *this;
}

gfm::math::Matrix2x2& gfm::math::Matrix2x2::operator /= (const gfm::math::Matrix2x2 & other) {
	GFM_DEBUG_ASSERT(false, GFM_STRING("MATRIX MATRIX DIVISION IS NOT IMPLEMENTED YET!"));
	return *this; // warning fix
}

gfm::math::Matrix2x2& gfm::math::Matrix2x2::operator /= (SkalarType skalar) {
	colums[0] /= skalar;
	colums[1] /= skalar;
	return *this;
}

gfm::math::Matrix2x2& gfm::math::Matrix2x2::operator ++() {
	++colums[0];
	++colums[1];
	return *this;
}

gfm::math::Matrix2x2& gfm::math::Matrix2x2::operator --() {
	--colums[0];
	--colums[1];
	return *this;
}

gfm::math::Matrix2x2 gfm::math::Matrix2x2::operator ++(int) {
	gfm::math::Matrix2x2 temp(*this);
	++*this;
	return temp;
}

gfm::math::Matrix2x2 gfm::math::Matrix2x2::operator --(int) {
	gfm::math::Matrix2x2 temp(*this);
	--*this;
	return temp;
}

gfm::math::Matrix2x2 gfm::math::operator +(const gfm::math::Matrix2x2 & mat) {
	return mat;
}

gfm::math::Matrix2x2 gfm::math::operator +(const gfm::math::Matrix2x2& left, const gfm::math::Matrix2x2& right) {
	return gfm::math::Matrix2x2
	(
		left[0] + right[0],
		left[1] + right[1]
	);
}

gfm::math::Matrix2x2 gfm::math::operator +(const gfm::math::Matrix2x2& left, gfm::math::Matrix2x2::SkalarType skalar) {
	return gfm::math::Matrix2x2(
		left[0] + skalar,
		left[1] + skalar
	);
}

gfm::math::Matrix2x2 gfm::math::operator +(gfm::math::Matrix2x2::SkalarType skalar, const gfm::math::Matrix2x2& right) {
	return gfm::math::Matrix2x2
	(
		skalar + right[0],
		skalar + right[1]
	);
}

gfm::math::Matrix2x2 gfm::math::operator -(const gfm::math::Matrix2x2& mat) {
	gfm::math::Matrix2x2 temp(-mat.col(0), -mat.col(1));
	return temp;
}

gfm::math::Matrix2x2 gfm::math::operator -(const gfm::math::Matrix2x2& left, const gfm::math::Matrix2x2& right) {
	return gfm::math::Matrix2x2
	(
		left[0] - right[0],
		left[1] - right[1]
	);
}

gfm::math::Matrix2x2 gfm::math::operator -(const gfm::math::Matrix2x2& left, gfm::math::Matrix2x2::SkalarType skalar) {
	return gfm::math::Matrix2x2(
		left[0] - skalar,
		left[1] - skalar
	);
}

gfm::math::Matrix2x2 gfm::math::operator -(gfm::math::Matrix2x2::SkalarType skalar, const gfm::math::Matrix2x2& right) {
	return gfm::math::Matrix2x2(
		skalar - right[0],
		skalar - right[1]
	);
}

gfm::math::Matrix2x2 gfm::math::operator * (const gfm::math::Matrix2x2& left, const gfm::math::Matrix2x2& right) {
	gfm::math::Matrix2x2 temp(left);
	return (temp *= right);
}

gfm::math::Matrix2x2 gfm::math::operator * (const gfm::math::Matrix2x2& left, gfm::math::Matrix2x2::SkalarType skalar) {
	return gfm::math::Matrix2x2(
		left[0] * skalar,
		left[1] * skalar
	);
}

gfm::math::Matrix2x2 gfm::math::operator * (gfm::math::Matrix2x2::SkalarType skalar, const gfm::math::Matrix2x2 & right) {
	return gfm::math::Matrix2x2(
		right[0] * skalar,
		right[1] * skalar
	);
}

gfm::math::Vector2D gfm::math::operator * (const gfm::math::Matrix2x2& left, const gfm::math::Vector2D& vec) {
	return gfm::math::Vector2D(
		left[0][0] * vec.x + left[1][0] * vec.y,
		left[0][1] * vec.x + left[1][1] * vec.y
	);
}

gfm::math::Vector2D gfm::math::operator * (const gfm::math::Vector2D& vec, const gfm::math::Matrix2x2 & right) {
	return gfm::math::Vector2D(
		vec.x * right[0][0] + vec.y * right[0][1],
		vec.x * right[1][0] + vec.y * right[1][1]
	);
}

gfm::math::Matrix2x2 gfm::math::operator / (const gfm::math::Matrix2x2& left, const gfm::math::Matrix2x2& right) {
	gfm::math::Matrix2x2 temp(left);
	return (temp /= right);
}

gfm::math::Matrix2x2 gfm::math::operator / (const gfm::math::Matrix2x2& left, gfm::math::Matrix2x2::SkalarType skalar) {
	return gfm::math::Matrix2x2(
		left[0] / skalar,
		left[1] / skalar
	);
}

gfm::math::Matrix2x2 gfm::math::operator / (gfm::math::Matrix2x2::SkalarType skalar, const gfm::math::Matrix2x2& right) {
	return gfm::math::Matrix2x2(
		right[0] / skalar,
		right[1] / skalar
	);
}

typename gfm::math::Matrix2x2::ColumType gfm::math::operator / (const gfm::math::Matrix2x2& left, const typename gfm::math::Matrix2x2::ColumType& vec) {
	return typename gfm::math::Matrix2x2::ColumType(
		left[0][0] / vec.x + left[1][0] / vec.y,
		left[0][1] / vec.x + left[1][1] / vec.y
	);
}

typename gfm::math::Matrix2x2::ColumType gfm::math::operator / (const typename gfm::math::Matrix2x2::ColumType & vec, const gfm::math::Matrix2x2 & right) {
	return typename gfm::math::Matrix2x2::ColumType(
		vec.x / right[0][0] + vec.y / right[0][1],
		vec.x / right[1][0] + vec.y / right[1][1]
	);
}

