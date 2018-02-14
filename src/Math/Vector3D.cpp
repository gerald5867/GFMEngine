#pragma once
#include <algorithm>
#include <stdexcept>
#include "Vector3D.h"
#include "Constants.h"
gfm::math::Vector3D::Vector3D(SkalarType x) {
	this->x = x;
	this->y = this->z = 0;
}

gfm::math::Vector3D::Vector3D(SkalarType x, SkalarType y) {
	this->x = x;
	this->y = y;
	this->z = 0;
}

gfm::math::Vector3D::Vector3D(SkalarType x, SkalarType y, SkalarType z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

gfm::math::Vector3D::Vector3D(const Vector2D& vec, SkalarType skalar) : 
Vector3D(vec.x, vec.y, skalar) {}

gfm::math::Vector3D::Vector3D(SkalarType skalar, const Vector2D& vec) : 
Vector3D(skalar, vec.x, vec.y) {}

gfm::math::Vector3D& gfm::math::Vector3D::operator += (SkalarType skalar) noexcept {
	x += skalar;
	y += skalar;
	z += skalar;
	return *this;
}

gfm::math::Vector3D& gfm::math::Vector3D::operator += (const Vector3D& vector) noexcept {
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

gfm::math::Vector3D& gfm::math::Vector3D::operator -= (SkalarType skalar) noexcept {
	x -= skalar;
	y -= skalar;
	z -= skalar;
	return *this;
}

gfm::math::Vector3D& gfm::math::Vector3D::operator -= (const Vector3D& vector) noexcept {
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

gfm::math::Vector3D& gfm::math::Vector3D::operator *= (SkalarType skalar) noexcept {
	x *= skalar;
	y *= skalar;
	z *= skalar;
	return *this;
}

gfm::math::Vector3D & gfm::math::Vector3D::operator *= (const Vector3D& vector) noexcept {
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	return *this;
}

gfm::math::Vector3D & gfm::math::Vector3D::operator /= (SkalarType skalar) {
	x /= skalar;
	y /= skalar;
	z /= skalar;
	return *this;
}

gfm::math::Vector3D & gfm::math::Vector3D::operator /= (const Vector3D& vector) {
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	return *this;
}

gfm::math::Vector3D & gfm::math::Vector3D::operator ++ () noexcept {
	++x;
	++y;
	++z;
	return *this;
}

gfm::math::Vector3D & gfm::math::Vector3D::operator -- () noexcept {
	--x;
	--y;
	--z;
	return *this;
}

gfm::math::Vector3D gfm::math::Vector3D::operator ++ (int) noexcept {
	gfm::math::Vector3D temp(*this);
	++*this;
	return temp;
}

gfm::math::Vector3D gfm::math::Vector3D::operator -- (int) noexcept {
	gfm::math::Vector3D temp(*this);
	--*this;
	return temp;
}

gfm::math::Vector3D::SkalarType& gfm::math::Vector3D::operator [](size_t index) {
	switch(index) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	}
	throw std::out_of_range("Vector index on operator [] is out of Range!");
	return x; // warning fix
}

const gfm::math::Vector3D::SkalarType& gfm::math::Vector3D::operator [](size_t index) const {
	switch(index) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	}
	throw std::out_of_range("Vector index on operator [] is out of Range!");
	return x; // warning fix
}

gfm::math::Vector2D gfm::math::Vector3D::xx()  const noexcept { return {x, x}; }
gfm::math::Vector2D gfm::math::Vector3D::xy()  const noexcept { return {x, y}; }
gfm::math::Vector2D gfm::math::Vector3D::xz()  const noexcept { return {x, z}; }
gfm::math::Vector2D gfm::math::Vector3D::yx()  const noexcept { return {y, x}; }
gfm::math::Vector2D gfm::math::Vector3D::yy()  const noexcept { return {y, y}; }
gfm::math::Vector2D gfm::math::Vector3D::yz()  const noexcept { return {y, z}; }
gfm::math::Vector2D gfm::math::Vector3D::zx()  const noexcept { return {z, x}; }
gfm::math::Vector2D gfm::math::Vector3D::zy()  const noexcept { return {z, y}; }
gfm::math::Vector2D gfm::math::Vector3D::zz()  const noexcept { return {z, z}; }

gfm::math::Vector3D gfm::math::Vector3D::xxx() const noexcept { return {x, x, x}; }
gfm::math::Vector3D gfm::math::Vector3D::xxy() const noexcept { return {x, x, y}; }
gfm::math::Vector3D gfm::math::Vector3D::xxz() const noexcept { return {x, x, z}; }
gfm::math::Vector3D gfm::math::Vector3D::xyx() const noexcept { return {x, y, x}; }
gfm::math::Vector3D gfm::math::Vector3D::xyy() const noexcept { return {x, y, y}; }
gfm::math::Vector3D gfm::math::Vector3D::xyz() const noexcept { return {x, y, z}; }
gfm::math::Vector3D gfm::math::Vector3D::xzx() const noexcept { return {x, z, x}; }
gfm::math::Vector3D gfm::math::Vector3D::xzy() const noexcept { return {x, z, y}; }
gfm::math::Vector3D gfm::math::Vector3D::xzz() const noexcept { return {x, z, z}; }
gfm::math::Vector3D gfm::math::Vector3D::yxx() const noexcept { return {y, x, x}; }
gfm::math::Vector3D gfm::math::Vector3D::yxy() const noexcept { return {y, x, y}; }
gfm::math::Vector3D gfm::math::Vector3D::yxz() const noexcept { return {y, x, z}; }
gfm::math::Vector3D gfm::math::Vector3D::yyx() const noexcept { return {y, y, x}; }
gfm::math::Vector3D gfm::math::Vector3D::yyy() const noexcept { return {y, y, y}; }
gfm::math::Vector3D gfm::math::Vector3D::yyz() const noexcept { return {y, y, z}; }
gfm::math::Vector3D gfm::math::Vector3D::yzx() const noexcept { return {y, z, x}; }
gfm::math::Vector3D gfm::math::Vector3D::yzy() const noexcept { return {y, z, y}; }
gfm::math::Vector3D gfm::math::Vector3D::yzz() const noexcept { return {y, z, z}; }
gfm::math::Vector3D gfm::math::Vector3D::zxx() const noexcept { return {z, x, x}; }
gfm::math::Vector3D gfm::math::Vector3D::zxy() const noexcept { return {z, x, y}; }
gfm::math::Vector3D gfm::math::Vector3D::zxz() const noexcept { return {z, x, z}; }
gfm::math::Vector3D gfm::math::Vector3D::zyx() const noexcept { return {y, z, x}; }
gfm::math::Vector3D gfm::math::Vector3D::zyy() const noexcept { return {z, y, y}; }
gfm::math::Vector3D gfm::math::Vector3D::zyz() const noexcept { return {z, y, z}; }
gfm::math::Vector3D gfm::math::Vector3D::zzx() const noexcept { return {z, z, x}; }
gfm::math::Vector3D gfm::math::Vector3D::zzy() const noexcept { return {z, z, y}; }
gfm::math::Vector3D gfm::math::Vector3D::zzz() const noexcept { return {z, z, z}; }

gfm::math::Vector3D gfm::math::Vector3D::RotateClockwise(float radians, Axis axis) const noexcept {
	float sin = std::sin(radians);
	float cos = std::cos(radians);

	switch(axis) {
	case Axis::eAXIS_X:
		return{
			x,
			cos * y - sin * z,
			sin * y + cos * z
		};
	case Axis::eAXIS_Y:
		return {
			x * cos + sin * z,
			y,
			x * -sin + cos * z
		};

	case Axis::eAXIS_Z:
		return {
			x * cos - sin * y,
			sin * x + cos * y,
			z
		};
	}

	return *this;
}

gfm::math::Vector3D gfm::math::Vector3D::RotateCounterClockwise(float radians, Axis axis) const noexcept {
	
	float sin = std::sin(radians);
	float cos = std::cos(radians);

	switch(axis) {
	case Axis::eAXIS_X:
		return{
			x,
			cos * y + sin * z,
			sin * y - cos * z
		};
	case Axis::eAXIS_Y:
		return {
			x * cos - sin * z,
			y,
			x * sin + cos * z
		};

	case Axis::eAXIS_Z:
		return {
			x * cos + sin * y,
			sin * x - cos * y,
			z
		};
	}
	return *this;
}

gfm::math::Vector3D gfm::math::Vector3D::Normalize() const noexcept {
	float len = Length();
	return (len == 0) ? gfm::math::Vector3D{1, 0, 0} : gfm::math::Vector3D{x / len, y / len, z / len};
}

gfm::math::Vector3D gfm::math::Vector3D::Abs()   const noexcept {
	return {std::abs(x), std::abs(y), std::abs(z)};
}

gfm::math::Vector3D gfm::math::Vector3D::Cross(const Vector3D& other) const noexcept {
	return {
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	};
}

gfm::math::Vector3D::SkalarType gfm::math::Vector3D::Length()const noexcept {
	return std::sqrt(LengthSq());
}

gfm::math::Vector3D::SkalarType gfm::math::Vector3D::LengthSq() const noexcept {
	return (x * x) + (y * y) + (z * z);
}

gfm::math::Vector3D::SkalarType gfm::math::Vector3D::Min()   const noexcept {
	return std::min(std::min(x, y), z);
}

gfm::math::Vector3D::SkalarType gfm::math::Vector3D::Max()   const noexcept {
	return std::max(std::max(x, y), z);
}

gfm::math::Vector3D::SkalarType gfm::math::Vector3D::Sum()   const noexcept {
	return x + y + z;
}

gfm::math::Vector3D::SkalarType gfm::math::Vector3D::Angle() const noexcept {
	float angle = std::acos(x / Length());
	return (y >= 0) ? angle : (math::PI * 2) - angle;
}

bool gfm::math::Vector3D::IsZero() const noexcept {
	return (x == 0) && (y == 0) && (z == 0);
}

gfm::math::Vector3D::SkalarType  gfm::math::Vector3D::Dot(const Vector3D& vec) const noexcept {
	return (x * vec.x) + (y * vec.y) + (z * vec.z);
}

gfm::math::Vector3D gfm::math::operator + (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept {
	gfm::math::Vector3D vec(
		left.x + right.x,
		left.y + right.y,
		left.z + right.z
	);
	return vec;
}

gfm::math::Vector3D gfm::math::operator + (gfm::math::Vector3D::SkalarType skalar, const gfm::math::Vector3D& right) noexcept {
	gfm::math::Vector3D vec(
		skalar + right.x,
		skalar + right.y,
		skalar + right.z
	);
	return vec;
}

gfm::math::Vector3D gfm::math::operator + (const gfm::math::Vector3D& left, gfm::math::Vector3D::SkalarType skalar) noexcept {
	gfm::math::Vector3D vec(
		left.x + skalar,
		left.y + skalar,
		left.z + skalar
	);
	return vec;
}

gfm::math::Vector3D gfm::math::operator + (const gfm::math::Vector3D& vec) noexcept {
	return vec;
}

gfm::math::Vector3D gfm::math::operator - (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) {
	gfm::math::Vector3D vec(
		left.x - right.x,
		left.y - right.y,
		left.z - right.z
	);
	return vec;
}

gfm::math::Vector3D gfm::math::operator - (gfm::math::Vector3D::SkalarType skalar, const gfm::math::Vector3D& right) noexcept {
	gfm::math::Vector3D vec(
		skalar - right.x,
		skalar - right.y,
		skalar - right.z
	);
	return vec;
}

gfm::math::Vector3D gfm::math::operator - (const gfm::math::Vector3D& left, gfm::math::Vector3D::SkalarType skalar) noexcept {
	gfm::math::Vector3D vec(
		left.x - skalar,
		left.y - skalar,
		left.z - skalar
	);
	return vec;

}

gfm::math::Vector3D gfm::math::operator - (const gfm::math::Vector3D& vec) noexcept {
	gfm::math::Vector3D temp(-vec.x, -vec.y, -vec.z);
	return temp;
}

gfm::math::Vector3D gfm::math::operator * (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept {
	gfm::math::Vector3D vec(
		left.x * right.x,
		left.y * right.y,
		left.z * right.z
	);
	return vec;
}

gfm::math::Vector3D gfm::math::operator * (gfm::math::Vector3D::SkalarType skalar, const gfm::math::Vector3D& right) noexcept {
	gfm::math::Vector3D vec(
		skalar * right.x,
		skalar * right.y,
		skalar * right.z
	);
	return vec;
}

gfm::math::Vector3D gfm::math::operator * (const gfm::math::Vector3D& left, gfm::math::Vector3D::SkalarType skalar) noexcept {
	gfm::math::Vector3D vec(
		left.x * skalar,
		left.y * skalar,
		left.z * skalar
	);
	return vec;
}

gfm::math::Vector3D gfm::math::operator / (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) {
	gfm::math::Vector3D vec(
		left.x / right.x,
		left.y / right.y,
		left.z / right.z
	);
	return vec;
}

gfm::math::Vector3D gfm::math::operator / (gfm::math::Vector3D::SkalarType skalar, const gfm::math::Vector3D& right) {
	gfm::math::Vector3D vec(
		skalar / right.x,
		skalar / right.y,
		skalar / right.z
	);
	return vec;
}

gfm::math::Vector3D gfm::math::operator / (const gfm::math::Vector3D & left, gfm::math::Vector3D::SkalarType skalar) {
	gfm::math::Vector3D vec(
		left.x / skalar,
		left.y / skalar,
		left.z / skalar
	);
	return vec;
}

bool gfm::math::operator || (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept {
	return (left.x && left.y) || (right.x && right.y) || (right.z && left.z);
}

bool gfm::math::operator && (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept {
	return (left.x && left.y) && (right.x && right.y) && (right.z && left.z);
}

bool gfm::math::operator == (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept {
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.y);
}

bool gfm::math::operator != (const gfm::math::Vector3D& left, const gfm::math::Vector3D& right) noexcept {
	return !(left == right);
}

#ifdef _MSC_VER
#pragma warning(push)
#endif