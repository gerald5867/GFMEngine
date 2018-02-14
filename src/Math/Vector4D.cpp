#pragma once
#include <stdexcept>
#include <algorithm>
#include "Vector4D.h"
#include "Constants.h"

gfm::math::Vector4D::Vector4D(SkalarType x) {
	this->x = x;
	y = z = w = 0;
}

gfm::math::Vector4D::Vector4D(SkalarType x, SkalarType y) {
	this->x = x;
	this->y = y;
	z = w = 0;
}

gfm::math::Vector4D::Vector4D(SkalarType x, SkalarType y, SkalarType z) {
	this->x = x;
	this->y = y;
	this->z = z;
	w = 0;
}

gfm::math::Vector4D::Vector4D(SkalarType x, SkalarType y, SkalarType z, SkalarType w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}


gfm::math::Vector4D::Vector4D(const Vector2D& vec, SkalarType first, SkalarType second):
	Vector4D(vec.x, vec.y, first, second) {}

gfm::math::Vector4D::Vector4D(SkalarType first, SkalarType second, const Vector2D& vec) :
	Vector4D(first, second, vec.x, vec.y) {}

gfm::math::Vector4D::Vector4D(SkalarType first, const Vector2D& vec, SkalarType second) :
	Vector4D(first, vec.x, vec.y, second) {}

gfm::math::Vector4D::Vector4D(const Vector2D& left, const Vector2D& right) :
	Vector4D(left.x, left.y, right.x, right.y) {}

gfm::math::Vector4D::Vector4D(const Vector3D& left, SkalarType skalar) :
	Vector4D(left.x, left.y, left.z, skalar) {}

gfm::math::Vector4D::Vector4D(SkalarType skalar, const Vector3D& left) :
	Vector4D(skalar, left.x, left.y, left.z) {}

gfm::math::Vector4D & gfm::math::Vector4D::operator += (SkalarType skalar) noexcept {
	x += skalar;
	y += skalar;
	z += skalar;
	w += skalar;
	return *this;
}

gfm::math::Vector4D & gfm::math::Vector4D::operator += (const gfm::math::Vector4D& vector) noexcept {
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
	return *this;
}

gfm::math::Vector4D& gfm::math::Vector4D::operator -= (SkalarType skalar) noexcept {
	x -= skalar;
	y -= skalar;
	z -= skalar;
	w -= skalar;
	return *this;
}

gfm::math::Vector4D& gfm::math::Vector4D::operator -= (const gfm::math::Vector4D& vector) noexcept {
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
	return *this;
}

gfm::math::Vector4D& gfm::math::Vector4D::operator *= (SkalarType skalar) noexcept {
	x *= skalar;
	y *= skalar;
	z *= skalar;
	w *= skalar;
	return *this;
}

gfm::math::Vector4D& gfm::math::Vector4D::operator *= (const gfm::math::Vector4D& vector) noexcept {
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w *= vector.w;
	return *this;
}

gfm::math::Vector4D& gfm::math::Vector4D::operator /= (SkalarType skalar) {
	x /= skalar;
	y /= skalar;
	z /= skalar;
	w /= skalar;
	return *this;
}

gfm::math::Vector4D& gfm::math::Vector4D::operator /= (const gfm::math::Vector4D& vector) {
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	w /= vector.w;
	return *this;
}

gfm::math::Vector4D& gfm::math::Vector4D::operator ++ () noexcept {
	++x;
	++y;
	++z;
	++w;
	return *this;
}

gfm::math::Vector4D& gfm::math::Vector4D::operator -- () noexcept {
	--x;
	--y;
	--z;
	--w;
	return *this;
}

gfm::math::Vector4D gfm::math::Vector4D::operator ++ (int) noexcept {
	Vector4D temp(*this);
	++*this;
	return temp;
}

gfm::math::Vector4D gfm::math::Vector4D::operator -- (int) noexcept {
	Vector4D temp(*this);
	--*this;
	return temp;
}

gfm::math::Vector4D::SkalarType& gfm::math::Vector4D::operator [](size_t index) {
	switch(index) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	}
	throw  std::out_of_range("Vector index on operator [] is out of Range!");
	return x; // warning fix
}

const  gfm::math::Vector4D::SkalarType& gfm::math::Vector4D::operator [](size_t index) const {
	switch(index) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	}
	throw  std::out_of_range("Vector index on operator [] is out of Range!");
	return x; // warning fix
}

gfm::math::Vector2D gfm::math::Vector4D::xx() const noexcept { return {x, x}; }
gfm::math::Vector2D gfm::math::Vector4D::xy() const noexcept { return {x, y}; }
gfm::math::Vector2D gfm::math::Vector4D::xz() const noexcept { return {x, z}; }
gfm::math::Vector2D gfm::math::Vector4D::xw() const noexcept { return {x, w}; }
gfm::math::Vector2D gfm::math::Vector4D::yx() const noexcept { return {y, x}; }
gfm::math::Vector2D gfm::math::Vector4D::yy() const noexcept { return {y, y}; }
gfm::math::Vector2D gfm::math::Vector4D::yz() const noexcept { return {y, z}; }
gfm::math::Vector2D gfm::math::Vector4D::yw() const noexcept { return {y, w}; }
gfm::math::Vector2D gfm::math::Vector4D::zx() const noexcept { return {z, x}; }
gfm::math::Vector2D gfm::math::Vector4D::zy() const noexcept { return {z, y}; }
gfm::math::Vector2D gfm::math::Vector4D::zz() const noexcept { return {z, z}; }
gfm::math::Vector2D gfm::math::Vector4D::zw() const noexcept { return {z, w}; }
gfm::math::Vector2D gfm::math::Vector4D::wx() const noexcept { return {w, x}; }
gfm::math::Vector2D gfm::math::Vector4D::wy() const noexcept { return {w, y}; }
gfm::math::Vector2D gfm::math::Vector4D::wz() const noexcept { return {w, z}; }
gfm::math::Vector2D gfm::math::Vector4D::ww() const noexcept { return {w, w}; }

gfm::math::Vector3D gfm::math::Vector4D::xxx() const noexcept { return {x, x, x}; }
gfm::math::Vector3D gfm::math::Vector4D::xxy() const noexcept { return {x, x, y}; }
gfm::math::Vector3D gfm::math::Vector4D::xxz() const noexcept { return {x, x, z}; }
gfm::math::Vector3D gfm::math::Vector4D::xxw() const noexcept { return {x, y, w}; }
gfm::math::Vector3D gfm::math::Vector4D::xyx() const noexcept { return {x, y, x}; }
gfm::math::Vector3D gfm::math::Vector4D::xyy() const noexcept { return {x, y, y}; }
gfm::math::Vector3D gfm::math::Vector4D::xyz() const noexcept { return {x, y, z}; }
gfm::math::Vector3D gfm::math::Vector4D::xyw() const noexcept { return {x, y, w}; }
gfm::math::Vector3D gfm::math::Vector4D::xzx() const noexcept { return {x, z, x}; }
gfm::math::Vector3D gfm::math::Vector4D::xzy() const noexcept { return {x, z, y}; }
gfm::math::Vector3D gfm::math::Vector4D::xzz() const noexcept { return {x, z, z}; }
gfm::math::Vector3D gfm::math::Vector4D::xzw() const noexcept { return {x, z, w}; }
gfm::math::Vector3D gfm::math::Vector4D::xwx() const noexcept { return {x, w, x}; }
gfm::math::Vector3D gfm::math::Vector4D::xwy() const noexcept { return {x, w, y}; }
gfm::math::Vector3D gfm::math::Vector4D::xwz() const noexcept { return {x, w, z}; }
gfm::math::Vector3D gfm::math::Vector4D::xww() const noexcept { return {x, w, w}; }
gfm::math::Vector3D gfm::math::Vector4D::yxx() const noexcept { return {y, x, x}; }
gfm::math::Vector3D gfm::math::Vector4D::yxy() const noexcept { return {y, x, y}; }
gfm::math::Vector3D gfm::math::Vector4D::yxz() const noexcept { return {y, x, z}; }
gfm::math::Vector3D gfm::math::Vector4D::yxw() const noexcept { return {y, x, w}; }
gfm::math::Vector3D gfm::math::Vector4D::yyx() const noexcept { return {y, y, x}; }
gfm::math::Vector3D gfm::math::Vector4D::yyy() const noexcept { return {y, y, y}; }
gfm::math::Vector3D gfm::math::Vector4D::yyz() const noexcept { return {y, y, z}; }
gfm::math::Vector3D gfm::math::Vector4D::yyw() const noexcept { return {y, y, w}; }
gfm::math::Vector3D gfm::math::Vector4D::yzx() const noexcept { return {y, z, x}; }
gfm::math::Vector3D gfm::math::Vector4D::yzy() const noexcept { return {y, z, y}; }
gfm::math::Vector3D gfm::math::Vector4D::yzz() const noexcept { return {y, z, z}; }
gfm::math::Vector3D gfm::math::Vector4D::yzw() const noexcept { return {y, z, w}; }
gfm::math::Vector3D gfm::math::Vector4D::ywx() const noexcept { return {y, w, x}; }
gfm::math::Vector3D gfm::math::Vector4D::ywy() const noexcept { return {y, w, y}; }
gfm::math::Vector3D gfm::math::Vector4D::ywz() const noexcept { return {y, w, z}; }
gfm::math::Vector3D gfm::math::Vector4D::yww() const noexcept { return {y, w, w}; }
gfm::math::Vector3D gfm::math::Vector4D::zxx() const noexcept { return {z, x, x}; }
gfm::math::Vector3D gfm::math::Vector4D::zxy() const noexcept { return {z, x, y}; }
gfm::math::Vector3D gfm::math::Vector4D::zxz() const noexcept { return {z, x, z}; }
gfm::math::Vector3D gfm::math::Vector4D::zxw() const noexcept { return {z, x, w}; }
gfm::math::Vector3D gfm::math::Vector4D::zyx() const noexcept { return {z, y, x}; }
gfm::math::Vector3D gfm::math::Vector4D::zyy() const noexcept { return {z, y, y}; }
gfm::math::Vector3D gfm::math::Vector4D::zyz() const noexcept { return {z, y, z}; }
gfm::math::Vector3D gfm::math::Vector4D::zyw() const noexcept { return {z, y, w}; }
gfm::math::Vector3D gfm::math::Vector4D::zzx() const noexcept { return {z, z, x}; }
gfm::math::Vector3D gfm::math::Vector4D::zzy() const noexcept { return {z, z, y}; }
gfm::math::Vector3D gfm::math::Vector4D::zzz() const noexcept { return {z, z, z}; }
gfm::math::Vector3D gfm::math::Vector4D::zzw() const noexcept { return {z, z, w}; }
gfm::math::Vector3D gfm::math::Vector4D::zwx() const noexcept { return {z, w, x}; }
gfm::math::Vector3D gfm::math::Vector4D::zwy() const noexcept { return {z, w, y}; }
gfm::math::Vector3D gfm::math::Vector4D::zwz() const noexcept { return {z, w, z}; }
gfm::math::Vector3D gfm::math::Vector4D::zww() const noexcept { return {z, w, w}; }
gfm::math::Vector3D gfm::math::Vector4D::wxx() const noexcept { return {w, x, x}; }
gfm::math::Vector3D gfm::math::Vector4D::wxy() const noexcept { return {w, x, y}; }
gfm::math::Vector3D gfm::math::Vector4D::wxz() const noexcept { return {w, x, z}; }
gfm::math::Vector3D gfm::math::Vector4D::wxw() const noexcept { return {w, x, w}; }
gfm::math::Vector3D gfm::math::Vector4D::wyx() const noexcept { return {w, y, x}; }
gfm::math::Vector3D gfm::math::Vector4D::wyy() const noexcept { return {w, y, y}; }
gfm::math::Vector3D gfm::math::Vector4D::wyz() const noexcept { return {w, y, z}; }
gfm::math::Vector3D gfm::math::Vector4D::wyw() const noexcept { return {w, y, w}; }
gfm::math::Vector3D gfm::math::Vector4D::wzx() const noexcept { return {w, z, x}; }
gfm::math::Vector3D gfm::math::Vector4D::wzy() const noexcept { return {w, z, y}; }
gfm::math::Vector3D gfm::math::Vector4D::wzz() const noexcept { return {w, z, z}; }
gfm::math::Vector3D gfm::math::Vector4D::wzw() const noexcept { return {w, z, w}; }
gfm::math::Vector3D gfm::math::Vector4D::wwx() const noexcept { return {w, w, x}; }
gfm::math::Vector3D gfm::math::Vector4D::wwy() const noexcept { return {w, w, y}; }
gfm::math::Vector3D gfm::math::Vector4D::wwz() const noexcept { return {w, w, z}; }
gfm::math::Vector3D gfm::math::Vector4D::www() const noexcept { return {w, w, w}; }

gfm::math::Vector4D gfm::math::Vector4D::xxxx() const noexcept { return {x, x, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xxxy() const noexcept { return {x, x, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xxxz() const noexcept { return {x, x, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xxxw() const noexcept { return {x, x, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xxyx() const noexcept { return {x, x, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xxyy() const noexcept { return {x, x, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xxyz() const noexcept { return {x, x, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xxyw() const noexcept { return {x, x, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xxzx() const noexcept { return {x, x, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xxzy() const noexcept { return {x, x, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xxzz() const noexcept { return {x, x, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xxzw() const noexcept { return {x, x, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xxwx() const noexcept { return {x, x, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xxwy() const noexcept { return {x, x, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xxwz() const noexcept { return {x, x, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xxww() const noexcept { return {x, x, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xyxx() const noexcept { return {x, y, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xyxy() const noexcept { return {x, y, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xyxz() const noexcept { return {x, y, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xyxw() const noexcept { return {x, y, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xyyx() const noexcept { return {x, y, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xyyy() const noexcept { return {x, y, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xyyz() const noexcept { return {x, y, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xyyw() const noexcept { return {x, y, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xyzx() const noexcept { return {x, y, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xyzy() const noexcept { return {x, y, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xyzz() const noexcept { return {x, y, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xyzw() const noexcept { return {x, y, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xywx() const noexcept { return {x, y, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xywy() const noexcept { return {x, y, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xywz() const noexcept { return {x, y, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xyww() const noexcept { return {x, y, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xzxx() const noexcept { return {x, z, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xzxy() const noexcept { return {x, z, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xzxz() const noexcept { return {x, z, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xzxw() const noexcept { return {x, z, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xzyx() const noexcept { return {x, z, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xzyy() const noexcept { return {x, z, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xzyz() const noexcept { return {x, z, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xzyw() const noexcept { return {x, z, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xzzx() const noexcept { return {x, z, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xzzy() const noexcept { return {x, z, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xzzz() const noexcept { return {x, z, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xzzw() const noexcept { return {x, z, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xzwx() const noexcept { return {x, z, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xzwy() const noexcept { return {x, z, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xzwz() const noexcept { return {x, z, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xzww() const noexcept { return {x, z, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xwxx() const noexcept { return {x, w, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xwxy() const noexcept { return {x, w, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xwxz() const noexcept { return {x, w, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xwxw() const noexcept { return {x, w, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xwyx() const noexcept { return {x, w, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xwyy() const noexcept { return {x, w, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xwyz() const noexcept { return {x, w, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xwyw() const noexcept { return {x, w, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xwzx() const noexcept { return {x, w, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xwzy() const noexcept { return {x, w, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xwzz() const noexcept { return {x, w, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xwzw() const noexcept { return {x, w, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::xwwx() const noexcept { return {x, w, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::xwwy() const noexcept { return {x, w, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::xwwz() const noexcept { return {x, w, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::xwww() const noexcept { return {x, w, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yxxx() const noexcept { return {y, x, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yxxy() const noexcept { return {y, x, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yxxz() const noexcept { return {y, x, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yxxw() const noexcept { return {y, x, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yxyx() const noexcept { return {y, x, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yxyy() const noexcept { return {y, x, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yxyz() const noexcept { return {y, x, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yxyw() const noexcept { return {y, x, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yxzx() const noexcept { return {y, x, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yxzy() const noexcept { return {y, x, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yxzz() const noexcept { return {y, x, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yxzw() const noexcept { return {y, x, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yxwx() const noexcept { return {y, x, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yxwy() const noexcept { return {y, x, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yxwz() const noexcept { return {y, x, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yxww() const noexcept { return {y, x, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yyxx() const noexcept { return {y, y, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yyxy() const noexcept { return {y, y, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yyxz() const noexcept { return {y, y, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yyxw() const noexcept { return {y, y, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yyyx() const noexcept { return {y, y, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yyyy() const noexcept { return {y, y, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yyyz() const noexcept { return {y, y, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yyyw() const noexcept { return {y, y, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yyzx() const noexcept { return {y, y, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yyzy() const noexcept { return {y, y, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yyzz() const noexcept { return {y, y, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yyzw() const noexcept { return {y, y, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yywx() const noexcept { return {y, y, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yywy() const noexcept { return {y, y, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yywz() const noexcept { return {y, y, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yyww() const noexcept { return {y, y, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yzxx() const noexcept { return {y, z, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yzxy() const noexcept { return {y, z, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yzxz() const noexcept { return {y, z, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yzxw() const noexcept { return {y, z, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yzyx() const noexcept { return {y, z, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yzyy() const noexcept { return {y, z, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yzyz() const noexcept { return {y, z, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yzyw() const noexcept { return {y, z, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yzzx() const noexcept { return {y, z, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yzzy() const noexcept { return {y, z, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yzzz() const noexcept { return {y, z, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yzzw() const noexcept { return {y, z, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::yzwx() const noexcept { return {y, z, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::yzwy() const noexcept { return {y, z, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::yzwz() const noexcept { return {y, z, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::yzww() const noexcept { return {y, z, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::ywxx() const noexcept { return {y, w, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::ywxy() const noexcept { return {y, w, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::ywxz() const noexcept { return {y, w, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::ywxw() const noexcept { return {y, w, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::ywyx() const noexcept { return {y, w, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::ywyy() const noexcept { return {y, w, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::ywyz() const noexcept { return {y, w, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::ywyw() const noexcept { return {y, w, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::ywzx() const noexcept { return {y, w, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::ywzy() const noexcept { return {y, w, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::ywzz() const noexcept { return {y, w, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::ywzw() const noexcept { return {y, w, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::ywwx() const noexcept { return {y, w, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::ywwy() const noexcept { return {y, w, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::ywwz() const noexcept { return {y, w, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::ywww() const noexcept { return {y, w, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zxxx() const noexcept { return {z, x, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zxxy() const noexcept { return {z, x, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zxxz() const noexcept { return {z, x, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zxxw() const noexcept { return {z, x, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zxyx() const noexcept { return {z, x, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zxyy() const noexcept { return {z, x, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zxyz() const noexcept { return {z, x, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zxyw() const noexcept { return {z, x, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zxzx() const noexcept { return {z, x, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zxzy() const noexcept { return {z, x, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zxzz() const noexcept { return {z, x, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zxzw() const noexcept { return {z, x, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zxwx() const noexcept { return {z, x, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zxwy() const noexcept { return {z, x, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zxwz() const noexcept { return {z, x, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zxww() const noexcept { return {z, x, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zyxx() const noexcept { return {z, y, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zyxy() const noexcept { return {z, y, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zyxz() const noexcept { return {z, y, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zyxw() const noexcept { return {z, y, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zyyx() const noexcept { return {z, y, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zyyy() const noexcept { return {z, y, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zyyz() const noexcept { return {z, y, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zyyw() const noexcept { return {z, y, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zyzx() const noexcept { return {z, y, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zyzy() const noexcept { return {z, y, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zyzz() const noexcept { return {z, y, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zyzw() const noexcept { return {z, y, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zywx() const noexcept { return {z, y, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zywy() const noexcept { return {z, y, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zywz() const noexcept { return {z, y, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zyww() const noexcept { return {z, y, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zzxx() const noexcept { return {z, z, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zzxy() const noexcept { return {z, z, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zzxz() const noexcept { return {z, z, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zzxw() const noexcept { return {z, z, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zzyx() const noexcept { return {z, z, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zzyy() const noexcept { return {z, z, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zzyz() const noexcept { return {z, z, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zzyw() const noexcept { return {z, z, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zzzx() const noexcept { return {z, z, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zzzy() const noexcept { return {z, z, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zzzz() const noexcept { return {z, z, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zzzw() const noexcept { return {z, z, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zzwx() const noexcept { return {z, z, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zzwy() const noexcept { return {z, z, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zzwz() const noexcept { return {z, z, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zzww() const noexcept { return {z, z, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zwxx() const noexcept { return {z, w, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zwxy() const noexcept { return {z, w, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zwxz() const noexcept { return {z, w, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zwxw() const noexcept { return {z, w, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zwyx() const noexcept { return {z, w, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zwyy() const noexcept { return {z, w, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zwyz() const noexcept { return {z, w, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zwyw() const noexcept { return {z, w, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zwzx() const noexcept { return {z, w, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zwzy() const noexcept { return {z, w, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zwzz() const noexcept { return {z, w, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zwzw() const noexcept { return {z, w, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::zwwx() const noexcept { return {z, w, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::zwwy() const noexcept { return {z, w, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::zwwz() const noexcept { return {z, w, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::zwww() const noexcept { return {z, w, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wxxx() const noexcept { return {w, x, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wxxy() const noexcept { return {w, x, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wxxz() const noexcept { return {w, x, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wxxw() const noexcept { return {w, x, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wxyx() const noexcept { return {w, x, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wxyy() const noexcept { return {w, x, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wxyz() const noexcept { return {w, x, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wxyw() const noexcept { return {w, x, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wxzx() const noexcept { return {w, x, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wxzy() const noexcept { return {w, x, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wxzz() const noexcept { return {w, x, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wxzw() const noexcept { return {w, x, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wxwx() const noexcept { return {w, x, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wxwy() const noexcept { return {w, x, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wxwz() const noexcept { return {w, x, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wxww() const noexcept { return {w, x, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wyxx() const noexcept { return {w, y, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wyxy() const noexcept { return {w, y, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wyxz() const noexcept { return {w, y, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wyxw() const noexcept { return {w, y, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wyyx() const noexcept { return {w, y, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wyyy() const noexcept { return {w, y, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wyyz() const noexcept { return {w, y, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wyyw() const noexcept { return {w, y, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wyzx() const noexcept { return {w, y, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wyzy() const noexcept { return {w, y, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wyzz() const noexcept { return {w, y, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wyzw() const noexcept { return {w, y, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wywx() const noexcept { return {w, y, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wywy() const noexcept { return {w, y, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wywz() const noexcept { return {w, y, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wyww() const noexcept { return {w, y, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wzxx() const noexcept { return {w, z, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wzxy() const noexcept { return {w, z, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wzxz() const noexcept { return {w, z, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wzxw() const noexcept { return {w, z, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wzyx() const noexcept { return {w, z, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wzyy() const noexcept { return {w, z, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wzyz() const noexcept { return {w, z, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wzyw() const noexcept { return {w, z, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wzzx() const noexcept { return {w, z, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wzzy() const noexcept { return {w, z, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wzzz() const noexcept { return {w, z, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wzzw() const noexcept { return {w, z, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wzwx() const noexcept { return {w, z, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wzwy() const noexcept { return {w, z, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wzwz() const noexcept { return {w, z, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wzww() const noexcept { return {w, z, w, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wwxx() const noexcept { return {w, w, x, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wwxy() const noexcept { return {w, w, x, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wwxz() const noexcept { return {w, w, x, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wwxw() const noexcept { return {w, w, x, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wwyx() const noexcept { return {w, w, y, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wwyy() const noexcept { return {w, w, y, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wwyz() const noexcept { return {w, w, y, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wwyw() const noexcept { return {w, w, y, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wwzx() const noexcept { return {w, w, z, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wwzy() const noexcept { return {w, w, z, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wwzz() const noexcept { return {w, w, z, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wwzw() const noexcept { return {w, w, z, w}; }
gfm::math::Vector4D gfm::math::Vector4D::wwwx() const noexcept { return {w, w, w, x}; }
gfm::math::Vector4D gfm::math::Vector4D::wwwy() const noexcept { return {w, w, w, y}; }
gfm::math::Vector4D gfm::math::Vector4D::wwwz() const noexcept { return {w, w, w, z}; }
gfm::math::Vector4D gfm::math::Vector4D::wwww() const noexcept { return {w, w, w, w}; }

gfm::math::Vector4D gfm::math::Vector4D::RotateClockwise(float radians, Axis axis) const noexcept {
	float sin = std::sin(radians);
	float cos = std::cos(radians);
	switch(axis) {
	case Axis::eAXIS_X:
		return{
			x,
			cos * y - sin * z,
			sin * y + cos * z,
			w
		};
	case Axis::eAXIS_Y:
		return {
			x * cos + sin * z,
			y,
			x * -sin + cos * z,
			w
		};

	case Axis::eAXIS_Z:
		return {
			x * cos - sin * y,
			sin * x + cos * y,
			z,
			w
		};
	}

	return *this;
}

gfm::math::Vector4D gfm::math::Vector4D::RotateCounterClockwise(float radians, Axis axis) const noexcept {
	float sin = std::sin(radians);
	float cos = std::cos(radians);

	switch(axis) {
	case Axis::eAXIS_X:
		return{
			x,
			cos * y + sin * z,
			sin * y - cos * z,
			w
		};
	case Axis::eAXIS_Y:
		return {
			x * cos - sin * z,
			y,
			x * sin + cos * z,
			w
		};
	case Axis::eAXIS_Z:
		return {
			x * cos + sin * y,
			sin * x - cos * y,
			z,
			w
		};
	}

	return *this;
}

gfm::math::Vector4D gfm::math::Vector4D::Normalize() const noexcept {
	float len = Length();
	return (len == 0) ? gfm::math::Vector4D{1, 0, 0, 0} : gfm::math::Vector4D{x / len, y / len, z / len, w};
}

gfm::math::Vector4D gfm::math::Vector4D::Abs()   const noexcept {
	return {std::abs(x), std::abs(y), std::abs(z), w};
}

gfm::math::Vector4D gfm::math::Vector4D::Cross(const gfm::math::Vector4D& other) const noexcept {
	return {
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x,
		w
	};
}

gfm::math::Vector4D::SkalarType gfm::math::Vector4D::Length() const noexcept {
	return std::sqrt(LengthSq());
}

gfm::math::Vector4D::SkalarType gfm::math::Vector4D::LengthSq() const noexcept {
	return (x * x) + (y * y) + (z * z);
}

gfm::math::Vector4D::SkalarType gfm::math::Vector4D::Min()   const noexcept {
	return std::min(std::min(x, y), z);
}

gfm::math::Vector4D::SkalarType gfm::math::Vector4D::Max()   const noexcept {
	return std::max(std::max(x, y), z);
}

gfm::math::Vector4D::SkalarType gfm::math::Vector4D::Sum()   const noexcept {
	return x + y + z;
}

gfm::math::Vector4D::SkalarType gfm::math::Vector4D::Angle() const noexcept {
	float angle = std::acos(x / Length());
	return (y >= 0) ? angle : (math::PI * 2) - angle;
}


bool gfm::math::Vector4D::IsZero() const noexcept {
	return (x == 0) && (y == 0) && (z == 0);
}

gfm::math::Vector4D::SkalarType gfm::math::Vector4D::Dot(const gfm::math::Vector4D& vec) const noexcept {
	return LengthSq();
}


gfm::math::Vector4D gfm::math::operator + (const gfm::math::Vector4D & left, const gfm::math::Vector4D& right) noexcept {
	gfm::math::Vector4D vec(
		left.x + right.x,
		left.y + right.y,
		left.z + right.z,
		left.w + right.w
	);
	return vec;
}

gfm::math::Vector4D gfm::math::operator + (gfm::math::Vector4D::SkalarType skalar, const gfm::math::Vector4D& right) noexcept {
	gfm::math::Vector4D vec(
		skalar + right.x,
		skalar + right.y,
		skalar + right.z,
		skalar + right.w
	);
	return vec;
}

gfm::math::Vector4D gfm::math::operator + (const gfm::math::Vector4D& left, gfm::math::Vector4D::SkalarType skalar) noexcept {
	gfm::math::Vector4D vec(
		left.x + skalar,
		left.y + skalar,
		left.z + skalar,
		left.w + skalar
		);
	return vec;
}

gfm::math::Vector4D gfm::math::operator + (const gfm::math::Vector4D& vec) noexcept {
	return vec;
}

gfm::math::Vector4D gfm::math::operator - (const gfm::math::Vector4D& left, const gfm::math::Vector4D& right) {
	gfm::math::Vector4D vec(
		left.x - right.x,
		left.y - right.y,
		left.z - right.z,
		left.w - right.w
	);
	return vec;
}

gfm::math::Vector4D gfm::math::operator - (gfm::math::Vector4D::SkalarType skalar, const gfm::math::Vector4D& right) noexcept {
	gfm::math::Vector4D vec(
		skalar - right.x,
		skalar - right.y,
		skalar - right.z,
		skalar - right.w
	);
	return vec;
}

gfm::math::Vector4D gfm::math::operator - (const gfm::math::Vector4D& left, gfm::math::Vector4D::SkalarType skalar) noexcept {
	gfm::math::Vector4D vec(
		left.x - skalar,
		left.y - skalar,
		left.z - skalar,
		left.w - skalar
	);
	return vec;

}

gfm::math::Vector4D gfm::math::operator - (const gfm::math::Vector4D& vec) noexcept {
	gfm::math::Vector4D temp(vec.x, vec.y, vec.z, vec.w);
	return temp;
}

gfm::math::Vector4D gfm::math::operator * (const gfm::math::Vector4D & left, const gfm::math::Vector4D& right) noexcept {
	gfm::math::Vector4D vec(
		left.x * right.x,
		left.y * right.y,
		left.z * right.z,
		left.w * right.w
	);
	return vec;
}

gfm::math::Vector4D gfm::math::operator * (gfm::math::Vector4D::SkalarType skalar, const gfm::math::Vector4D & right) noexcept {
	gfm::math::Vector4D vec(
		skalar * right.x,
		skalar * right.y,
		skalar * right.z,
		skalar * right.w
	);
	return vec;
}

gfm::math::Vector4D gfm::math::operator * (const gfm::math::Vector4D & left, gfm::math::Vector4D::SkalarType skalar) noexcept {
	gfm::math::Vector4D vec(
		left.x * skalar,
		left.y * skalar,
		left.z * skalar,
		left.w * skalar
	);
	return vec;
}

gfm::math::Vector4D gfm::math::operator / (const gfm::math::Vector4D & left, const gfm::math::Vector4D& right) {
	gfm::math::Vector4D vec(
		left.x / right.x,
		left.y / right.y,
		left.z / right.z,
		left.w / right.w
	);
	return vec;
}

gfm::math::Vector4D gfm::math::operator / (gfm::math::Vector4D::SkalarType skalar, const gfm::math::Vector4D & right) {
	gfm::math::Vector4D vec(
		skalar / right.x,
		skalar / right.y,
		skalar / right.z,
		skalar / right.w
	);
	return vec;
}

gfm::math::Vector4D gfm::math::operator / (const gfm::math::Vector4D & left, gfm::math::Vector4D::SkalarType skalar) {
	gfm::math::Vector4D vec(
		left.x / skalar,
		left.y / skalar,
		left.z / skalar,
		left.w / skalar
	);
	return vec;
}

bool gfm::math::operator || (const gfm::math::Vector4D& left, const gfm::math::Vector4D& right) noexcept {
	return (left.x && left.y) || (right.x && right.y) || (right.z && right.w) || (left.z && left.w);
}

bool gfm::math::operator && (const gfm::math::Vector4D& left, const gfm::math::Vector4D& right) noexcept {
	return (left.x && left.y) && (right.x && right.y) && (right.z && right.w) && (left.z && left.w);
}

bool gfm::math::operator == (const gfm::math::Vector4D& left, const gfm::math::Vector4D& right) noexcept {
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
}

bool gfm::math::operator != (const gfm::math::Vector4D& left, const gfm::math::Vector4D& right) noexcept {
	return !(left == right);
}