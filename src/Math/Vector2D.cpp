#pragma once
#include <stdexcept>
#include <algorithm>
#include "Matrix2x2.h"
#include "Vector2D.h"

gfm::math::Vector2D::Vector2D(SkalarType x, SkalarType y) {
	this->x = x;
	this->y = y;
}

gfm::math::Vector2D::Vector2D(SkalarType skalar) {
	this->x = this->y = skalar;
}

gfm::math::Vector2D& gfm::math::Vector2D::operator += (SkalarType skalar) noexcept {
	x += skalar;
	y += skalar;
	return *this;
}

gfm::math::Vector2D& gfm::math::Vector2D::operator += (const Vector2D& other) noexcept {
	x += other.x;
	y += other.y;
	return *this;
}

gfm::math::Vector2D& gfm::math::Vector2D::operator -= (SkalarType skalar) noexcept {
	x -= skalar;
	y -= skalar;
	return *this;
}

gfm::math::Vector2D& gfm::math::Vector2D::operator -= (const Vector2D& other) noexcept {
	x -= other.x;
	y -= other.y;
	return *this;
}

gfm::math::Vector2D & gfm::math::Vector2D::operator *= (SkalarType skalar) noexcept {
	x *= skalar;
	y *= skalar;
	return *this;
}

gfm::math::Vector2D & gfm::math::Vector2D::operator *= (const Vector2D& other) noexcept {
	x *= other.x;
	y *= other.y;
	return *this;
}

gfm::math::Vector2D & gfm::math::Vector2D::operator *= (const Matrix2x2& mat) noexcept {
	*this = *this * mat;
	return *this;
}

gfm::math::Vector2D & gfm::math::Vector2D::operator /= (SkalarType skalar) {
	x /= skalar;
	y /= skalar;
	return *this;
}

gfm::math::Vector2D & gfm::math::Vector2D::operator /= (const Vector2D& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

gfm::math::Vector2D & gfm::math::Vector2D::operator ++ () noexcept {
	++x;
	++y;
	return *this;
}

gfm::math::Vector2D & gfm::math::Vector2D::operator -- () noexcept {
	--x;
	--y;
	return *this;
}

gfm::math::Vector2D gfm::math::Vector2D::operator ++ (int) noexcept {
	gfm::math::Vector2D temp(*this);
	++*this;
	return temp;
}

gfm::math::Vector2D gfm::math::Vector2D::operator -- (int) noexcept {
	gfm::math::Vector2D temp(*this);
	--*this;
	return temp;
}

gfm::math::Vector2D::SkalarType& gfm::math::Vector2D::operator [](size_t index) {
	switch(index) {
	case 0: return x;
	case 1: return y;
	}
	throw  std::range_error("Vector index on operator [] is out of Range!");
	return x; // warning fix
}

const gfm::math::Vector2D::SkalarType& gfm::math::Vector2D::operator [](size_t index) const {
	switch(index) {
	case 0: return x;
	case 1: return y;
	}
	throw  std::range_error("Vector index on operator [] is out of Range!");
	return x; // warning fix
}

gfm::math::Vector2D  gfm::math::Vector2D::xx() const noexcept { return {x, x}; }
gfm::math::Vector2D  gfm::math::Vector2D::xy() const noexcept { return {x, y}; }
gfm::math::Vector2D  gfm::math::Vector2D::yx() const noexcept { return {y, x}; }
gfm::math::Vector2D  gfm::math::Vector2D::yy() const noexcept { return {y, y}; }

gfm::math::Vector2D gfm::math::Vector2D::RotateClockwise(SkalarType radians) const noexcept {
	SkalarType sin = std::sin(radians);
	SkalarType cos = std::cos(radians);
	return {
		x * cos - y * sin,
		x * sin + y * cos
	};
}

gfm::math::Vector2D gfm::math::Vector2D::RotateCounterClockwise(SkalarType radians) const noexcept {
	SkalarType sin = std::sin(radians);
	SkalarType cos = std::cos(radians);

	return {
		x * cos + y * sin,
		x * sin - y * cos
	};
}

gfm::math::Vector2D gfm::math::Vector2D::Normalize() const noexcept {
	SkalarType len = Length();
	return (len == 0) ? gfm::math::Vector2D{1, 0} : gfm::math::Vector2D{x / len, y / len};
}

gfm::math::Vector2D gfm::math::Vector2D::Abs()   const noexcept {
	return {std::abs(x), std::abs(y)};
}

gfm::math::Vector2D::SkalarType gfm::math::Vector2D::Cross(const gfm::math::Vector2D& other) const noexcept {
	return (x * other.y) - (other.x * y);
}

gfm::math::Vector2D::SkalarType gfm::math::Vector2D::Length()const noexcept {
	return std::sqrt(LengthSq());
}

gfm::math::Vector2D::SkalarType gfm::math::Vector2D::LengthSq() const noexcept {
	return (x * x) + (y * y);
}

gfm::math::Vector2D::SkalarType gfm::math::Vector2D::Min()   const noexcept {
	return std::min(x, y);
}

gfm::math::Vector2D::SkalarType gfm::math::Vector2D::Max()   const noexcept {
	return std::max(x, y);
}

gfm::math::Vector2D::SkalarType gfm::math::Vector2D::Sum()   const noexcept {
	return x + y;
}

gfm::math::Vector2D::SkalarType gfm::math::Vector2D::Angle() const noexcept {
	SkalarType angle = std::acos(x / Length());
	return (y >= 0) ? angle : (math::PI * 2) - angle;
}

bool gfm::math::Vector2D::IsZero() const noexcept {
	return (x == 0) && (y == 0);
}

gfm::math::Vector2D::SkalarType gfm::math::Vector2D::Dot(const gfm::math::Vector2D& vec) const noexcept {
	return (x * vec.x) + (y * vec.y);
}

gfm::math::Vector2D gfm::math::operator + (const gfm::math::Vector2D & left, const gfm::math::Vector2D & right) noexcept {
	gfm::math::Vector2D vec(left.x + right.x ,left.y + right.y);
	return vec;
}

gfm::math::Vector2D gfm::math::operator + (gfm::math::Vector2D::SkalarType skalar, const gfm::math::Vector2D& right) noexcept {
	gfm::math::Vector2D vec(skalar + right.x, skalar + right.y);
	return vec;
}

gfm::math::Vector2D gfm::math::operator + (const gfm::math::Vector2D& left, gfm::math::Vector2D::SkalarType skalar) noexcept {
	gfm::math::Vector2D vec(left.x + skalar, left.y + skalar);
	return vec;
}

gfm::math::Vector2D gfm::math::operator + (const gfm::math::Vector2D& vec) noexcept {
	return vec;
}

gfm::math::Vector2D gfm::math::operator - (const gfm::math::Vector2D& left, const gfm::math::Vector2D& right) {
	gfm::math::Vector2D vec(left.x - right.x, left.y - right.y);
	return vec;
}

gfm::math::Vector2D gfm::math::operator - (gfm::math::Vector2D::SkalarType skalar, const gfm::math::Vector2D& right) noexcept {
	gfm::math::Vector2D vec(skalar - right.x, skalar - right.y);
	return vec;
}

gfm::math::Vector2D gfm::math::operator - (const gfm::math::Vector2D& left, gfm::math::Vector2D::SkalarType skalar) noexcept {
	gfm::math::Vector2D vec(left.x - skalar, left.y - skalar);
	return vec;

}

gfm::math::Vector2D gfm::math::operator - (const gfm::math::Vector2D& vec) noexcept {
	gfm::math::Vector2D(-vec.x, -vec.y);
	return vec;
}

gfm::math::Vector2D gfm::math::operator * (const gfm::math::Vector2D& left, const gfm::math::Vector2D& right) noexcept {
	gfm::math::Vector2D vec(left.x * right.x, left.y * right.y);
	return vec;
}

gfm::math::Vector2D gfm::math::operator * (gfm::math::Vector2D::SkalarType skalar, const gfm::math::Vector2D& right) noexcept {
	gfm::math::Vector2D vec(skalar * right.x, skalar * right.y);
	return vec;
}

gfm::math::Vector2D gfm::math::operator * (const gfm::math::Vector2D& left, gfm::math::Vector2D::SkalarType skalar) noexcept {
	gfm::math::Vector2D vec(left.x * skalar, left.y * skalar);
	return vec;
}

gfm::math::Vector2D gfm::math::operator / (const gfm::math::Vector2D& left, const gfm::math::Vector2D& right) {
	gfm::math::Vector2D vec(left.x / right.x, left.y / right.y);
	return vec;
}

gfm::math::Vector2D gfm::math::operator / (gfm::math::Vector2D::SkalarType skalar, const gfm::math::Vector2D& right) {
	gfm::math::Vector2D vec(skalar / right.x, skalar / right.y);
	return vec;
}

gfm::math::Vector2D gfm::math::operator / (const gfm::math::Vector2D& left, gfm::math::Vector2D::SkalarType skalar) {
	gfm::math::Vector2D vec(left.x / skalar, left.y / skalar);
	return vec;
}

bool gfm::math::operator || (const gfm::math::Vector2D & left, const gfm::math::Vector2D & right) noexcept {
	return (left.x && left.y) || (right.x && right.y);
}

bool gfm::math::operator && (const gfm::math::Vector2D& left, const gfm::math::Vector2D& right) noexcept {
	return (left.x && left.y) && (right.x && right.y);
}

bool gfm::math::operator == (const gfm::math::Vector2D& left, const gfm::math::Vector2D & right) noexcept {
	return (left.x == right.x) && (left.y == right.y);
}

bool gfm::math::operator != (const gfm::math::Vector2D & left, const gfm::math::Vector2D & right) noexcept {
	return !(left == right);
}
