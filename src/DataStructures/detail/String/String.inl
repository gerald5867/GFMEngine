#pragma once
#include <assert.h>
#include "StringVarArgWrapper.h"
#include "StringVarArgMaxLen.h"
#include "CompileTimeString.h"
#include "../../../Algorithm/Sum.h"
#include "../../../Utils/Logger.h"
#include "../../../TypeTraits/VariadicIsFormatType.h"

GFM_BEST_INLINE bool gfm::String::UsesSSO() const noexcept {
	return m_ssoArray[ms_SSOSIZE] == 1;
}

GFM_BEST_INLINE void gfm::String::SetUseSSO() noexcept {
	m_ssoArray[ms_SSOSIZE] = 1;
}

GFM_BEST_INLINE void gfm::String::SetUseNoSSO() noexcept {
	m_ssoArray[ms_SSOSIZE] = 0;
}

GFM_BEST_INLINE void gfm::String::ZeroInitialize() noexcept {
	memset(m_ssoArray, 0, (ms_SSOSIZE + 1) * sizeof(CharType));

}

GFM_BEST_INLINE const gfm::String::CharType* gfm::String::Raw() const noexcept {
	return (UsesSSO()) ? m_ssoArray : m_ptr;
}
GFM_BEST_INLINE gfm::String::CharType* gfm::String::Raw() noexcept {
	return (UsesSSO()) ? m_ssoArray : m_ptr;
}

GFM_BEST_INLINE const gfm::String::CharType * gfm::String::CStr() const noexcept
{
	return Raw();
}

GFM_BEST_INLINE gfm::String::CharType * gfm::String::CStr() noexcept {
	return Raw();
}

GFM_BEST_INLINE gfm::String::SizeType gfm::String::Length() const noexcept {
	return m_length;
}

GFM_BEST_INLINE gfm::String::SizeType gfm::String::Capacity() const noexcept {
	return m_capacity;
}

GFM_BEST_INLINE const gfm::String::CharType * gfm::String::cbegin() const noexcept {
	return Raw();
}

GFM_BEST_INLINE const gfm::String::CharType * gfm::String::cend()   const noexcept {
	return Raw() + Length();
}

GFM_BEST_INLINE const gfm::String::CharType * gfm::String::begin()  const noexcept {
	return Raw();
}

GFM_BEST_INLINE const gfm::String::CharType * gfm::String::end() const noexcept {
	return Raw() + Length();
}

GFM_BEST_INLINE gfm::String::CharType * gfm::String::begin() noexcept {
	return Raw();
}

GFM_BEST_INLINE gfm::String::CharType * gfm::String::end()   noexcept {
	return Raw() + Length();
}

GFM_BEST_INLINE gfm::String::CharType& gfm::String::Append(CharType ch) noexcept {
	GrowIfToSmall(1);
	return Raw()[m_length++] = ch;
}

GFM_BEST_INLINE bool gfm::String::Empty() const noexcept {
	return m_length == 0;
}

GFM_BEST_INLINE gfm::String operator"" _gs(const char * str, std::size_t) {
	return gfm::String(str);
}

GFM_BEST_INLINE gfm::String operator"" _gs(const wchar_t * str, std::size_t) {
	return gfm::String(str);
}

GFM_BEST_INLINE std::ostream& gfm::operator << (std::ostream& os, const gfm::String& str) {
	os << str.Raw();
	return os;
}

GFM_BEST_INLINE gfm::String gfm::operator +(const String& left, const String& right) {
	String result(left);
	return result += right;
}

GFM_BEST_INLINE gfm::String gfm::operator +(const char* str, const String& right) {
	String result(str);
	return result += right;
}

GFM_BEST_INLINE gfm::String gfm::operator +(const String& left, const char* str) {
	String result(left);
	return result += str;
}
GFM_BEST_INLINE gfm::String gfm::operator +(const wchar_t* str, const String& right) {
	String result(str);
	return result += right;
}
GFM_BEST_INLINE gfm::String gfm::operator +(const String& left, const wchar_t* str) {
	String result(left);
	return result += str;
}

GFM_BEST_INLINE gfm::String gfm::operator +(const String& left, const gfm::List<char>& other) {
	String result(left);
	return result += other;
}

GFM_BEST_INLINE gfm::String gfm::operator +(const String& left, const gfm::List<wchar_t>& other) {
	String result(left);
	return result += other;
}
GFM_BEST_INLINE gfm::String gfm::operator +(const gfm::List<char>& other, const String& right) {
	String result(other);
	return result += right;
}

GFM_BEST_INLINE gfm::String gfm::operator +(const gfm::List<wchar_t>& other, const String& right) {
	String result(other);
	return result += right;
}

GFM_BEST_INLINE gfm::String gfm::operator *(const String& left, typename String::SizeType skalar) {
	String result(left);
	return result *= skalar;
}
GFM_BEST_INLINE gfm::String gfm::operator *(typename String::SizeType skalar, const String& right) {
	String result(right);
	return result *= skalar;
}

template<typename Allocator>
gfm::String::String(const List<wchar_t, Allocator>& lst) {
	InitializeFromCharPtr(lst.Raw(), lst.Length());
}

template<typename Allocator>
gfm::String::String(const List<char, Allocator>& lst) {
	InitializeFromCharPtr(lst.Raw(), lst.Length());
}

template<typename Allocator>
gfm::String::String(const List<wchar_t, Allocator>& lst, SizeType length) {
	InitializeFromCharPtr(lst.Raw(), length);
}
template<typename Allocator>
gfm::String::String(const List<char, Allocator>& lst, SizeType length) {
	InitializeFromCharPtr(lst.Raw(), length);
}

template<template<typename, typename = std::allocator<wchar_t>> class Container> // STL CONTAINER
gfm::String::String(const Container<wchar_t>& stlContainer) {
	InitializeFromCharPtr(stlContainer.data(), stlContainer.size());
}

template<template<typename, typename = std::allocator<char>> class Container> // STL CONTAINER
gfm::String::String(const Container<char>& stlContainer) {
	InitializeFromCharPtr(stlContainer.data(), stlContainer.size());
}

template<template<typename, typename = std::allocator<wchar_t>> class Container> // STL CONTAINER
gfm::String::String(const Container<wchar_t>& stlContainer, SizeType length) {
	InitializeFromCharPtr(stlContainer.data(), length);
}
template<template<typename, typename = std::allocator<char>> class Container> // STL CONTAINER
gfm::String::String(const Container<char>& stlContainer, SizeType length) {
	InitializeFromCharPtr(stlContainer.data(), length);
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4544)
//TO STRING METHODEN !!
//ÜERLADEN MIT NUR 2 ARGUMENTEN

template<typename... ArgPackTypes, typename Dummy = typename std::enable_if<(sizeof...(ArgPackTypes) >= 1)>::type >
void gfm::String::FormatBuffer(const CharType* format, String& result, ArgPackTypes&&... arguments) {
	//static_assert(traits::AllFormatType<ArgPackTypes...>::value, "Illegal Type was passed into String::FormatBuffer / String::Format");
	FormatVarArg varArgs[] = { FormatVarArg(arguments)... };
	auto formatLen = detail::CStringHelper::Len(format);
	SizeType totalLen = algorithm::Sum<SizeType, FormatVarArg>(varArgs, sizeof...(ArgPackTypes), 
		[](const FormatVarArg& arg)->SizeType { return arg.Length();
	}) + formatLen + 1;
	if (result.m_capacity - result.m_length <= totalLen) {
		result.Grow(totalLen);
	}
	auto* resultRawPtr = result.Raw();
	struct numberWithlen { utils::int32 Number; utils::uint32 Len; };
	auto numberLambda = [](const CharType* strNumber)->decltype(auto) {
		thread_local static CharType tempNumber[32];
		SizeType i = 0;
		for (; strNumber[i] != '}'; ++i) {
			tempNumber[i] = strNumber[i];
		}
		tempNumber[i + 1] = '\0';
		return numberWithlen{ detail::CStringHelper::ToInt(tempNumber, i), i };
	};
	numberWithlen currentFormatIndex = {};
	SizeType index = 0;
	for (SizeType i = 0; i < formatLen;) {
		if (format[i] == '{' && i + 1 < formatLen && format[i + 1] != '{' && isdigit(format[i + 1])) {
			currentFormatIndex = numberLambda(&format[i + 1]);
			index = currentFormatIndex.Number;
#		if GFM_IS_DEBUG_MODE
			if (index >= sizeof...(ArgPackTypes)) { assert(false); } // ASSERT kann nicht benutzt werden weil assert diese Methode benutzt!
#		endif
			const auto& varArg = varArgs[index];
			result.GrowIfToSmall(varArg.Length());
			detail::CStringHelper::Copy(resultRawPtr + result.m_length, varArg.CStr(), varArg.Length());
			result.m_length += varArg.Length();
			resultRawPtr = result.Raw();
			i += currentFormatIndex.Len + 2;
			continue;
		}
		resultRawPtr[result.m_length++] = format[i++];
		if (result.m_length >= result.m_capacity) { assert(false); }
	}
	resultRawPtr[result.m_length] = '\0';
}

template<typename ...ArgPackTypes, typename Dummy = typename std::enable_if<(sizeof...(ArgPackTypes) >= 1)>::type>
gfm::String gfm::String::Format(const CharType* format, ArgPackTypes&&... arguments) {
	String result;
	FormatBuffer(format, result, std::forward<ArgPackTypes&&>(arguments)...);
	return result;
}

#pragma  warning(pop)
#endif //MSC_VER

template<typename CharPtrType>
void gfm::String::InitializeFromCharPtr(const CharPtrType* str, SizeType initLen) {
	static_assert(std::is_same<CharPtrType, wchar_t>::value || std::is_same<CharPtrType, char>::value,
		"ERROR InitializeFromCharPtr illegal type was passed in, only wchar_t and char allowed !");
	ZeroInitialize();
	auto len = (initLen > 0) ? initLen : detail::CStringHelper::Len(str);
	m_length = len;
	if (len < (ms_SSOSIZE - 1)) {
		SetUseSSO();
		detail::CStringHelper::Copy(m_ssoArray, str, len);
		m_capacity = ms_SSOSIZE;
	}
	else {
		SetUseNoSSO();
		m_ptr = static_cast<CharType*>(m_allocator.Allocate(((len + 1) * sizeof(CharType))));
		detail::CStringHelper::Copy(m_ptr, str, len);
		m_capacity = len + 1;
	}
}

template<typename RawCharType>
void gfm::String::AppendRawStr(const RawCharType* str, SizeType len) {
	GrowIfToSmall(len);
	detail::CStringHelper::Copy(Raw() + m_length, str, len);
	m_length += len;
}