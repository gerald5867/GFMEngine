#pragma once
#ifndef STRING_VAR_ARG_WRAPPER_H
#define STRING_VAR_ARG_WRAPPER_H
#include <stdexcept>
#include "String.h"
#include "../../../Utils/Types.h"
namespace gfm 
{
namespace detail 
{
	class ArgWrapper final
	{
	public:
		enum class WrapedType {
			eTYPE_VOID,
			eTYPE_CHAR,
			eTYPE_UCHAR,
			eTYPE_WCHAR,
			eTYPE_SHORT,
			eTYPE_USHORT,
			eTYPE_INT,
			eTYPE_UINT,
			eTYPE_LONG,
			eTYPE_ULONG,
			eTYPE_LONGLONG,
			eTYPE_ULONGLONG,
			eTYPE_FLOAT,
			eTYPE_DOUBLE,
			eTYPE_LONGDOUBLE,
			eTYPE_UCHARPTR,
			eTYPE_CHARPTR,
			eTYPE_WCHARPTR,
			eTYPE_STRING,
		};
		constexpr explicit ArgWrapper(char) : m_wrappedType(WrapedType::eTYPE_CHAR){}
		constexpr explicit ArgWrapper(unsigned char) : m_wrappedType(WrapedType::eTYPE_UCHAR) {}
		constexpr explicit ArgWrapper(wchar_t) : m_wrappedType(WrapedType::eTYPE_CHAR) {}
		constexpr explicit ArgWrapper(short) : m_wrappedType(WrapedType::eTYPE_SHORT) {}
		constexpr explicit ArgWrapper(unsigned short) : m_wrappedType(WrapedType::eTYPE_USHORT) {}
		constexpr explicit ArgWrapper(int) : m_wrappedType(WrapedType::eTYPE_INT) {}
		constexpr explicit ArgWrapper(unsigned int) : m_wrappedType(WrapedType::eTYPE_UINT) {}
		constexpr explicit ArgWrapper(long) : m_wrappedType(WrapedType::eTYPE_LONG) {}
		constexpr explicit ArgWrapper(unsigned long) : m_wrappedType(WrapedType::eTYPE_ULONG) {}
		constexpr explicit ArgWrapper(long long) : m_wrappedType(WrapedType::eTYPE_LONGLONG) {}
		constexpr explicit ArgWrapper(unsigned long long) : m_wrappedType(WrapedType::eTYPE_ULONGLONG) {}
		constexpr explicit ArgWrapper(float) : m_wrappedType(WrapedType::eTYPE_FLOAT) {}
		constexpr explicit ArgWrapper(double) : m_wrappedType(WrapedType::eTYPE_DOUBLE) {}
		constexpr explicit ArgWrapper(long double) : m_wrappedType(WrapedType::eTYPE_LONGDOUBLE) {}
		constexpr explicit ArgWrapper(const char*) : m_wrappedType(WrapedType::eTYPE_CHARPTR) {}
		constexpr explicit ArgWrapper(const unsigned char*) : m_wrappedType(WrapedType::eTYPE_UCHARPTR) {}
		constexpr explicit ArgWrapper(const wchar_t*) : m_wrappedType(WrapedType::eTYPE_WCHARPTR) {}
		constexpr explicit ArgWrapper(const String&) : m_wrappedType(WrapedType::eTYPE_STRING) {}
		constexpr explicit ArgWrapper(String&) : m_wrappedType(WrapedType::eTYPE_STRING) {}
	public:
		constexpr WrapedType Type() const noexcept { return m_wrappedType; }
	private:
		WrapedType m_wrappedType = WrapedType::eTYPE_VOID;
	};
}//detail
}//gfm
#endif //STRING_VAR_ARG_WRAPPER_H