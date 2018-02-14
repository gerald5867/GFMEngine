#pragma once
#ifndef VECTOR4D_H
#define VECTOR4D_H
#include "Vector2D.h"
#include "Vector3D.h"
#include <cmath>
#include "Constants.h"
#include "..\Macro\ApiCall.h"

namespace gfm {
namespace math {

struct Vector4D
{
	using SkalarType = float;
	union
	{
		struct
		{
			SkalarType x;
			SkalarType y;
			SkalarType z;
			SkalarType w;
		};
		struct
		{
			SkalarType r;
			SkalarType g;
			SkalarType b;
			SkalarType a;
		};
		struct
		{
			SkalarType u;
			SkalarType v;
			SkalarType w;
			SkalarType t;
		};
	};
	GFM_APICALL Vector4D() = default;

	GFM_APICALL Vector4D(SkalarType x);
	GFM_APICALL Vector4D(SkalarType x, SkalarType y);
	GFM_APICALL Vector4D(SkalarType x, SkalarType y, SkalarType z);
	GFM_APICALL Vector4D(SkalarType x, SkalarType y, SkalarType z, SkalarType w);

	GFM_APICALL Vector4D(const Vector2D& vec, SkalarType first, SkalarType second);
	GFM_APICALL Vector4D(SkalarType first, SkalarType second, const Vector2D& vec);
	GFM_APICALL Vector4D(SkalarType first, const Vector2D& vec, SkalarType second);
	GFM_APICALL Vector4D(const Vector2D& left, const Vector2D& right);
	GFM_APICALL Vector4D(const Vector3D& left, SkalarType skalar);
	GFM_APICALL Vector4D(SkalarType skalar, const Vector3D& left);

	GFM_APICALL Vector4D(const Vector4D& other) = default;
	GFM_APICALL Vector4D(Vector4D&& other) = default;
	GFM_APICALL Vector4D & operator = (const Vector4D& other) = default;
	GFM_APICALL Vector4D & operator = (Vector4D&& other) = default;

	GFM_APICALL Vector4D & operator += (SkalarType skalar) noexcept;
	GFM_APICALL Vector4D & operator += (const Vector4D& vector) noexcept;

	GFM_APICALL Vector4D & operator -= (SkalarType skalar) noexcept;
	GFM_APICALL Vector4D & operator -= (const Vector4D& vector) noexcept;

	GFM_APICALL Vector4D & operator *= (SkalarType skalar) noexcept;
	GFM_APICALL Vector4D & operator *= (const Vector4D& vector) noexcept;

	GFM_APICALL Vector4D & operator /= (SkalarType skalar);
	GFM_APICALL Vector4D & operator /= (const Vector4D& vector);


	GFM_APICALL Vector4D & operator ++ () noexcept;
	GFM_APICALL Vector4D & operator -- () noexcept;
	GFM_APICALL Vector4D operator ++ (int) noexcept;
	GFM_APICALL Vector4D operator -- (int) noexcept;

	GFM_APICALL SkalarType & operator [](size_t index);
	GFM_APICALL const SkalarType & operator [](size_t index) const;

	GFM_APICALL Vector4D Cross(const Vector4D& other) const noexcept;
	GFM_APICALL SkalarType Dot(const Vector4D& vec) const noexcept;

	GFM_APICALL Vector4D RotateClockwise(float radians, Axis axis) const noexcept;
	GFM_APICALL Vector4D RotateCounterClockwise(float radians, Axis axis) const noexcept;
	GFM_APICALL Vector4D Normalize() const noexcept;
	GFM_APICALL Vector4D Abs()   const noexcept;
	GFM_APICALL SkalarType Length()const noexcept;
	GFM_APICALL SkalarType LengthSq() const noexcept;
	GFM_APICALL SkalarType Min()   const noexcept;
	GFM_APICALL SkalarType Max()   const noexcept;
	GFM_APICALL SkalarType Sum()   const noexcept;
	GFM_APICALL SkalarType Angle() const noexcept;
	GFM_APICALL bool IsZero() const noexcept;

#ifdef _MSC_VER
#pragma region SwizzleOperators
#endif
	GFM_APICALL Vector2D xx() const noexcept;
	GFM_APICALL Vector2D xy() const noexcept;
	GFM_APICALL Vector2D xz() const noexcept;
	GFM_APICALL Vector2D xw() const noexcept;
	GFM_APICALL Vector2D yx() const noexcept;
	GFM_APICALL Vector2D yy() const noexcept;
	GFM_APICALL Vector2D yz() const noexcept;
	GFM_APICALL Vector2D yw() const noexcept;
	GFM_APICALL Vector2D zx() const noexcept;
	GFM_APICALL Vector2D zy() const noexcept;
	GFM_APICALL Vector2D zz() const noexcept;
	GFM_APICALL Vector2D zw() const noexcept;
	GFM_APICALL Vector2D wx() const noexcept;
	GFM_APICALL Vector2D wy() const noexcept;
	GFM_APICALL Vector2D wz() const noexcept;
	GFM_APICALL Vector2D ww() const noexcept;

	GFM_APICALL Vector3D xxx() const noexcept;
	GFM_APICALL Vector3D xxy() const noexcept;
	GFM_APICALL Vector3D xxz() const noexcept;
	GFM_APICALL Vector3D xxw() const noexcept;
	GFM_APICALL Vector3D xyx() const noexcept;
	GFM_APICALL Vector3D xyy() const noexcept;
	GFM_APICALL Vector3D xyz() const noexcept;
	GFM_APICALL Vector3D xyw() const noexcept;
	GFM_APICALL Vector3D xzx() const noexcept;
	GFM_APICALL Vector3D xzy() const noexcept;
	GFM_APICALL Vector3D xzz() const noexcept;
	GFM_APICALL Vector3D xzw() const noexcept;
	GFM_APICALL Vector3D xwx() const noexcept;
	GFM_APICALL Vector3D xwy() const noexcept;
	GFM_APICALL Vector3D xwz() const noexcept;
	GFM_APICALL Vector3D xww() const noexcept;
	GFM_APICALL Vector3D yxx() const noexcept;
	GFM_APICALL Vector3D yxy() const noexcept;
	GFM_APICALL Vector3D yxz() const noexcept;
	GFM_APICALL Vector3D yxw() const noexcept;
	GFM_APICALL Vector3D yyx() const noexcept;
	GFM_APICALL Vector3D yyy() const noexcept;
	GFM_APICALL Vector3D yyz() const noexcept;
	GFM_APICALL Vector3D yyw() const noexcept;
	GFM_APICALL Vector3D yzx() const noexcept;
	GFM_APICALL Vector3D yzy() const noexcept;
	GFM_APICALL Vector3D yzz() const noexcept;
	GFM_APICALL Vector3D yzw() const noexcept;
	GFM_APICALL Vector3D ywx() const noexcept;
	GFM_APICALL Vector3D ywy() const noexcept;
	GFM_APICALL Vector3D ywz() const noexcept;
	GFM_APICALL Vector3D yww() const noexcept;
	GFM_APICALL Vector3D zxx() const noexcept;
	GFM_APICALL Vector3D zxy() const noexcept;
	GFM_APICALL Vector3D zxz() const noexcept;
	GFM_APICALL Vector3D zxw() const noexcept;
	GFM_APICALL Vector3D zyx() const noexcept;
	GFM_APICALL Vector3D zyy() const noexcept;
	GFM_APICALL Vector3D zyz() const noexcept;
	GFM_APICALL Vector3D zyw() const noexcept;
	GFM_APICALL Vector3D zzx() const noexcept;
	GFM_APICALL Vector3D zzy() const noexcept;
	GFM_APICALL Vector3D zzz() const noexcept;
	GFM_APICALL Vector3D zzw() const noexcept;
	GFM_APICALL Vector3D zwx() const noexcept;
	GFM_APICALL Vector3D zwy() const noexcept;
	GFM_APICALL Vector3D zwz() const noexcept;
	GFM_APICALL Vector3D zww() const noexcept;
	GFM_APICALL Vector3D wxx() const noexcept;
	GFM_APICALL Vector3D wxy() const noexcept;
	GFM_APICALL Vector3D wxz() const noexcept;
	GFM_APICALL Vector3D wxw() const noexcept;
	GFM_APICALL Vector3D wyx() const noexcept;
	GFM_APICALL Vector3D wyy() const noexcept;
	GFM_APICALL Vector3D wyz() const noexcept;
	GFM_APICALL Vector3D wyw() const noexcept;
	GFM_APICALL Vector3D wzx() const noexcept;
	GFM_APICALL Vector3D wzy() const noexcept;
	GFM_APICALL Vector3D wzz() const noexcept;
	GFM_APICALL Vector3D wzw() const noexcept;
	GFM_APICALL Vector3D wwx() const noexcept;
	GFM_APICALL Vector3D wwy() const noexcept;
	GFM_APICALL Vector3D wwz() const noexcept;
	GFM_APICALL Vector3D www() const noexcept;

	GFM_APICALL Vector4D xxxx() const noexcept;
	GFM_APICALL Vector4D xxxy() const noexcept;
	GFM_APICALL Vector4D xxxz() const noexcept;
	GFM_APICALL Vector4D xxxw() const noexcept;
	GFM_APICALL Vector4D xxyx() const noexcept;
	GFM_APICALL Vector4D xxyy() const noexcept;
	GFM_APICALL Vector4D xxyz() const noexcept;
	GFM_APICALL Vector4D xxyw() const noexcept;
	GFM_APICALL Vector4D xxzx() const noexcept;
	GFM_APICALL Vector4D xxzy() const noexcept;
	GFM_APICALL Vector4D xxzz() const noexcept;
	GFM_APICALL Vector4D xxzw() const noexcept;
	GFM_APICALL Vector4D xxwx() const noexcept;
	GFM_APICALL Vector4D xxwy() const noexcept;
	GFM_APICALL Vector4D xxwz() const noexcept;
	GFM_APICALL Vector4D xxww() const noexcept;
	GFM_APICALL Vector4D xyxx() const noexcept;
	GFM_APICALL Vector4D xyxy() const noexcept;
	GFM_APICALL Vector4D xyxz() const noexcept;
	GFM_APICALL Vector4D xyxw() const noexcept;
	GFM_APICALL Vector4D xyyx() const noexcept;
	GFM_APICALL Vector4D xyyy() const noexcept;
	GFM_APICALL Vector4D xyyz() const noexcept;
	GFM_APICALL Vector4D xyyw() const noexcept;
	GFM_APICALL Vector4D xyzx() const noexcept;
	GFM_APICALL Vector4D xyzy() const noexcept;
	GFM_APICALL Vector4D xyzz() const noexcept;
	GFM_APICALL Vector4D xyzw() const noexcept;
	GFM_APICALL Vector4D xywx() const noexcept;
	GFM_APICALL Vector4D xywy() const noexcept;
	GFM_APICALL Vector4D xywz() const noexcept;
	GFM_APICALL Vector4D xyww() const noexcept;
	GFM_APICALL Vector4D xzxx() const noexcept;
	GFM_APICALL Vector4D xzxy() const noexcept;
	GFM_APICALL Vector4D xzxz() const noexcept;
	GFM_APICALL Vector4D xzxw() const noexcept;
	GFM_APICALL Vector4D xzyx() const noexcept;
	GFM_APICALL Vector4D xzyy() const noexcept;
	GFM_APICALL Vector4D xzyz() const noexcept;
	GFM_APICALL Vector4D xzyw() const noexcept;
	GFM_APICALL Vector4D xzzx() const noexcept;
	GFM_APICALL Vector4D xzzy() const noexcept;
	GFM_APICALL Vector4D xzzz() const noexcept;
	GFM_APICALL Vector4D xzzw() const noexcept;
	GFM_APICALL Vector4D xzwx() const noexcept;
	GFM_APICALL Vector4D xzwy() const noexcept;
	GFM_APICALL Vector4D xzwz() const noexcept;
	GFM_APICALL Vector4D xzww() const noexcept;
	GFM_APICALL Vector4D xwxx() const noexcept;
	GFM_APICALL Vector4D xwxy() const noexcept;
	GFM_APICALL Vector4D xwxz() const noexcept;
	GFM_APICALL Vector4D xwxw() const noexcept;
	GFM_APICALL Vector4D xwyx() const noexcept;
	GFM_APICALL Vector4D xwyy() const noexcept;
	GFM_APICALL Vector4D xwyz() const noexcept;
	GFM_APICALL Vector4D xwyw() const noexcept;
	GFM_APICALL Vector4D xwzx() const noexcept;
	GFM_APICALL Vector4D xwzy() const noexcept;
	GFM_APICALL Vector4D xwzz() const noexcept;
	GFM_APICALL Vector4D xwzw() const noexcept;
	GFM_APICALL Vector4D xwwx() const noexcept;
	GFM_APICALL Vector4D xwwy() const noexcept;
	GFM_APICALL Vector4D xwwz() const noexcept;
	GFM_APICALL Vector4D xwww() const noexcept;
	GFM_APICALL Vector4D yxxx() const noexcept;
	GFM_APICALL Vector4D yxxy() const noexcept;
	GFM_APICALL Vector4D yxxz() const noexcept;
	GFM_APICALL Vector4D yxxw() const noexcept;
	GFM_APICALL Vector4D yxyx() const noexcept;
	GFM_APICALL Vector4D yxyy() const noexcept;
	GFM_APICALL Vector4D yxyz() const noexcept;
	GFM_APICALL Vector4D yxyw() const noexcept;
	GFM_APICALL Vector4D yxzx() const noexcept;
	GFM_APICALL Vector4D yxzy() const noexcept;
	GFM_APICALL Vector4D yxzz() const noexcept;
	GFM_APICALL Vector4D yxzw() const noexcept;
	GFM_APICALL Vector4D yxwx() const noexcept;
	GFM_APICALL Vector4D yxwy() const noexcept;
	GFM_APICALL Vector4D yxwz() const noexcept;
	GFM_APICALL Vector4D yxww() const noexcept;
	GFM_APICALL Vector4D yyxx() const noexcept;
	GFM_APICALL Vector4D yyxy() const noexcept;
	GFM_APICALL Vector4D yyxz() const noexcept;
	GFM_APICALL Vector4D yyxw() const noexcept;
	GFM_APICALL Vector4D yyyx() const noexcept;
	GFM_APICALL Vector4D yyyy() const noexcept;
	GFM_APICALL Vector4D yyyz() const noexcept;
	GFM_APICALL Vector4D yyyw() const noexcept;
	GFM_APICALL Vector4D yyzx() const noexcept;
	GFM_APICALL Vector4D yyzy() const noexcept;
	GFM_APICALL Vector4D yyzz() const noexcept;
	GFM_APICALL Vector4D yyzw() const noexcept;
	GFM_APICALL Vector4D yywx() const noexcept;
	GFM_APICALL Vector4D yywy() const noexcept;
	GFM_APICALL Vector4D yywz() const noexcept;
	GFM_APICALL Vector4D yyww() const noexcept;
	GFM_APICALL Vector4D yzxx() const noexcept;
	GFM_APICALL Vector4D yzxy() const noexcept;
	GFM_APICALL Vector4D yzxz() const noexcept;
	GFM_APICALL Vector4D yzxw() const noexcept;
	GFM_APICALL Vector4D yzyx() const noexcept;
	GFM_APICALL Vector4D yzyy() const noexcept;
	GFM_APICALL Vector4D yzyz() const noexcept;
	GFM_APICALL Vector4D yzyw() const noexcept;
	GFM_APICALL Vector4D yzzx() const noexcept;
	GFM_APICALL Vector4D yzzy() const noexcept;
	GFM_APICALL Vector4D yzzz() const noexcept;
	GFM_APICALL Vector4D yzzw() const noexcept;
	GFM_APICALL Vector4D yzwx() const noexcept;
	GFM_APICALL Vector4D yzwy() const noexcept;
	GFM_APICALL Vector4D yzwz() const noexcept;
	GFM_APICALL Vector4D yzww() const noexcept;
	GFM_APICALL Vector4D ywxx() const noexcept;
	GFM_APICALL Vector4D ywxy() const noexcept;
	GFM_APICALL Vector4D ywxz() const noexcept;
	GFM_APICALL Vector4D ywxw() const noexcept;
	GFM_APICALL Vector4D ywyx() const noexcept;
	GFM_APICALL Vector4D ywyy() const noexcept;
	GFM_APICALL Vector4D ywyz() const noexcept;
	GFM_APICALL Vector4D ywyw() const noexcept;
	GFM_APICALL Vector4D ywzx() const noexcept;
	GFM_APICALL Vector4D ywzy() const noexcept;
	GFM_APICALL Vector4D ywzz() const noexcept;
	GFM_APICALL Vector4D ywzw() const noexcept;
	GFM_APICALL Vector4D ywwx() const noexcept;
	GFM_APICALL Vector4D ywwy() const noexcept;
	GFM_APICALL Vector4D ywwz() const noexcept;
	GFM_APICALL Vector4D ywww() const noexcept;
	GFM_APICALL Vector4D zxxx() const noexcept;
	GFM_APICALL Vector4D zxxy() const noexcept;
	GFM_APICALL Vector4D zxxz() const noexcept;
	GFM_APICALL Vector4D zxxw() const noexcept;
	GFM_APICALL Vector4D zxyx() const noexcept;
	GFM_APICALL Vector4D zxyy() const noexcept;
	GFM_APICALL Vector4D zxyz() const noexcept;
	GFM_APICALL Vector4D zxyw() const noexcept;
	GFM_APICALL Vector4D zxzx() const noexcept;
	GFM_APICALL Vector4D zxzy() const noexcept;
	GFM_APICALL Vector4D zxzz() const noexcept;
	GFM_APICALL Vector4D zxzw() const noexcept;
	GFM_APICALL Vector4D zxwx() const noexcept;
	GFM_APICALL Vector4D zxwy() const noexcept;
	GFM_APICALL Vector4D zxwz() const noexcept;
	GFM_APICALL Vector4D zxww() const noexcept;
	GFM_APICALL Vector4D zyxx() const noexcept;
	GFM_APICALL Vector4D zyxy() const noexcept;
	GFM_APICALL Vector4D zyxz() const noexcept;
	GFM_APICALL Vector4D zyxw() const noexcept;
	GFM_APICALL Vector4D zyyx() const noexcept;
	GFM_APICALL Vector4D zyyy() const noexcept;
	GFM_APICALL Vector4D zyyz() const noexcept;
	GFM_APICALL Vector4D zyyw() const noexcept;
	GFM_APICALL Vector4D zyzx() const noexcept;
	GFM_APICALL Vector4D zyzy() const noexcept;
	GFM_APICALL Vector4D zyzz() const noexcept;
	GFM_APICALL Vector4D zyzw() const noexcept;
	GFM_APICALL Vector4D zywx() const noexcept;
	GFM_APICALL Vector4D zywy() const noexcept;
	GFM_APICALL Vector4D zywz() const noexcept;
	GFM_APICALL Vector4D zyww() const noexcept;
	GFM_APICALL Vector4D zzxx() const noexcept;
	GFM_APICALL Vector4D zzxy() const noexcept;
	GFM_APICALL Vector4D zzxz() const noexcept;
	GFM_APICALL Vector4D zzxw() const noexcept;
	GFM_APICALL Vector4D zzyx() const noexcept;
	GFM_APICALL Vector4D zzyy() const noexcept;
	GFM_APICALL Vector4D zzyz() const noexcept;
	GFM_APICALL Vector4D zzyw() const noexcept;
	GFM_APICALL Vector4D zzzx() const noexcept;
	GFM_APICALL Vector4D zzzy() const noexcept;
	GFM_APICALL Vector4D zzzz() const noexcept;
	GFM_APICALL Vector4D zzzw() const noexcept;
	GFM_APICALL Vector4D zzwx() const noexcept;
	GFM_APICALL Vector4D zzwy() const noexcept;
	GFM_APICALL Vector4D zzwz() const noexcept;
	GFM_APICALL Vector4D zzww() const noexcept;
	GFM_APICALL Vector4D zwxx() const noexcept;
	GFM_APICALL Vector4D zwxy() const noexcept;
	GFM_APICALL Vector4D zwxz() const noexcept;
	GFM_APICALL Vector4D zwxw() const noexcept;
	GFM_APICALL Vector4D zwyx() const noexcept;
	GFM_APICALL Vector4D zwyy() const noexcept;
	GFM_APICALL Vector4D zwyz() const noexcept;
	GFM_APICALL Vector4D zwyw() const noexcept;
	GFM_APICALL Vector4D zwzx() const noexcept;
	GFM_APICALL Vector4D zwzy() const noexcept;
	GFM_APICALL Vector4D zwzz() const noexcept;
	GFM_APICALL Vector4D zwzw() const noexcept;
	GFM_APICALL Vector4D zwwx() const noexcept;
	GFM_APICALL Vector4D zwwy() const noexcept;
	GFM_APICALL Vector4D zwwz() const noexcept;
	GFM_APICALL Vector4D zwww() const noexcept;
	GFM_APICALL Vector4D wxxx() const noexcept;
	GFM_APICALL Vector4D wxxy() const noexcept;
	GFM_APICALL Vector4D wxxz() const noexcept;
	GFM_APICALL Vector4D wxxw() const noexcept;
	GFM_APICALL Vector4D wxyx() const noexcept;
	GFM_APICALL Vector4D wxyy() const noexcept;
	GFM_APICALL Vector4D wxyz() const noexcept;
	GFM_APICALL Vector4D wxyw() const noexcept;
	GFM_APICALL Vector4D wxzx() const noexcept;
	GFM_APICALL Vector4D wxzy() const noexcept;
	GFM_APICALL Vector4D wxzz() const noexcept;
	GFM_APICALL Vector4D wxzw() const noexcept;
	GFM_APICALL Vector4D wxwx() const noexcept;
	GFM_APICALL Vector4D wxwy() const noexcept;
	GFM_APICALL Vector4D wxwz() const noexcept;
	GFM_APICALL Vector4D wxww() const noexcept;
	GFM_APICALL Vector4D wyxx() const noexcept;
	GFM_APICALL Vector4D wyxy() const noexcept;
	GFM_APICALL Vector4D wyxz() const noexcept;
	GFM_APICALL Vector4D wyxw() const noexcept;
	GFM_APICALL Vector4D wyyx() const noexcept;
	GFM_APICALL Vector4D wyyy() const noexcept;
	GFM_APICALL Vector4D wyyz() const noexcept;
	GFM_APICALL Vector4D wyyw() const noexcept;
	GFM_APICALL Vector4D wyzx() const noexcept;
	GFM_APICALL Vector4D wyzy() const noexcept;
	GFM_APICALL Vector4D wyzz() const noexcept;
	GFM_APICALL Vector4D wyzw() const noexcept;
	GFM_APICALL Vector4D wywx() const noexcept;
	GFM_APICALL Vector4D wywy() const noexcept;
	GFM_APICALL Vector4D wywz() const noexcept;
	GFM_APICALL Vector4D wyww() const noexcept;
	GFM_APICALL Vector4D wzxx() const noexcept;
	GFM_APICALL Vector4D wzxy() const noexcept;
	GFM_APICALL Vector4D wzxz() const noexcept;
	GFM_APICALL Vector4D wzxw() const noexcept;
	GFM_APICALL Vector4D wzyx() const noexcept;
	GFM_APICALL Vector4D wzyy() const noexcept;
	GFM_APICALL Vector4D wzyz() const noexcept;
	GFM_APICALL Vector4D wzyw() const noexcept;
	GFM_APICALL Vector4D wzzx() const noexcept;
	GFM_APICALL Vector4D wzzy() const noexcept;
	GFM_APICALL Vector4D wzzz() const noexcept;
	GFM_APICALL Vector4D wzzw() const noexcept;
	GFM_APICALL Vector4D wzwx() const noexcept;
	GFM_APICALL Vector4D wzwy() const noexcept;
	GFM_APICALL Vector4D wzwz() const noexcept;
	GFM_APICALL Vector4D wzww() const noexcept;
	GFM_APICALL Vector4D wwxx() const noexcept;
	GFM_APICALL Vector4D wwxy() const noexcept;
	GFM_APICALL Vector4D wwxz() const noexcept;
	GFM_APICALL Vector4D wwxw() const noexcept;
	GFM_APICALL Vector4D wwyx() const noexcept;
	GFM_APICALL Vector4D wwyy() const noexcept;
	GFM_APICALL Vector4D wwyz() const noexcept;
	GFM_APICALL Vector4D wwyw() const noexcept;
	GFM_APICALL Vector4D wwzx() const noexcept;
	GFM_APICALL Vector4D wwzy() const noexcept;
	GFM_APICALL Vector4D wwzz() const noexcept;
	GFM_APICALL Vector4D wwzw() const noexcept;
	GFM_APICALL Vector4D wwwx() const noexcept;
	GFM_APICALL Vector4D wwwy() const noexcept;
	GFM_APICALL Vector4D wwwz() const noexcept;
	GFM_APICALL Vector4D wwww() const noexcept;
#ifdef _MSC_VER
#pragma endregion SwizzleOperators
#endif
};
GFM_APICALL gfm::math::Vector4D operator + (const gfm::math::Vector4D & left, const gfm::math::Vector4D& right) noexcept;
GFM_APICALL gfm::math::Vector4D operator + (gfm::math::Vector4D::SkalarType skalar, const gfm::math::Vector4D& right) noexcept;
GFM_APICALL gfm::math::Vector4D operator + (const gfm::math::Vector4D& left, gfm::math::Vector4D::SkalarType skalar) noexcept;
GFM_APICALL gfm::math::Vector4D operator + (const gfm::math::Vector4D& vec) noexcept;

GFM_APICALL gfm::math::Vector4D operator - (const gfm::math::Vector4D& left, const gfm::math::Vector4D& right);
GFM_APICALL gfm::math::Vector4D operator - (gfm::math::Vector4D::SkalarType skalar, const gfm::math::Vector4D& right) noexcept;
GFM_APICALL gfm::math::Vector4D operator - (const gfm::math::Vector4D& left, gfm::math::Vector4D::SkalarType skalar) noexcept;
GFM_APICALL gfm::math::Vector4D operator - (const gfm::math::Vector4D& vec) noexcept;

GFM_APICALL gfm::math::Vector4D operator * (const gfm::math::Vector4D & left, const gfm::math::Vector4D& right) noexcept;
GFM_APICALL gfm::math::Vector4D operator * (gfm::math::Vector4D::SkalarType skalar, const gfm::math::Vector4D & right) noexcept;
GFM_APICALL gfm::math::Vector4D operator * (const gfm::math::Vector4D & left, gfm::math::Vector4D::SkalarType skalar) noexcept;

GFM_APICALL gfm::math::Vector4D operator / (const gfm::math::Vector4D & left, const gfm::math::Vector4D& right);
GFM_APICALL gfm::math::Vector4D operator / (gfm::math::Vector4D::SkalarType skalar, const gfm::math::Vector4D & right);
GFM_APICALL gfm::math::Vector4D operator / (const gfm::math::Vector4D & left, gfm::math::Vector4D::SkalarType skalar);

GFM_APICALL bool operator || (const gfm::math::Vector4D& left, const gfm::math::Vector4D& right) noexcept;
GFM_APICALL bool operator && (const gfm::math::Vector4D& left, const gfm::math::Vector4D& right) noexcept;
GFM_APICALL bool operator == (const gfm::math::Vector4D& left, const gfm::math::Vector4D& right) noexcept;
GFM_APICALL bool operator != (const gfm::math::Vector4D& left, const gfm::math::Vector4D& right) noexcept;

} // namespace math	
} // namespace gfm

#endif // VECTOR4D_H