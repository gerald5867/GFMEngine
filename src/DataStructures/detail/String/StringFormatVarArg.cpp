#pragma once
#include "String.h"

gfm::String::FormatVarArg::FormatVarArg(const char* str) :
m_tempBuffer(nullptr) {
	memset(m_buffer, 0, sizeof(CharType) * (ms_BUFFER_SIZE + 1));
#if GFM_PLATFORM_WINDOWS
	m_length = detail::CStringHelper::Len(str);
	if(m_length <= ms_BUFFER_SIZE) {
		detail::CStringHelper::Convert(str, m_buffer, ms_BUFFER_SIZE);
		m_ptrInitialized = false;
	}
	else {
		m_tempBuffer = static_cast<CharType*>(memory::DefaultAllocator::Allocate( (m_length+1) * sizeof(CharType)));
		detail::CStringHelper::Convert(str, m_tempBuffer.Raw(), m_length);
		m_ptr = m_tempBuffer.Raw();
		m_ptrInitialized = true;
	}
#else
	m_ptr = str;
	m_length = detail::CStringHelper::Len(m_ptr);
	m_ptrInitialized = true;
#endif
}

gfm::String::FormatVarArg::FormatVarArg(const unsigned char* str) : 
FormatVarArg(reinterpret_cast<const char*>(str)) {
}

gfm::String::FormatVarArg::FormatVarArg(const wchar_t* str) : 
m_tempBuffer(nullptr) {
	memset(m_buffer, 0, sizeof(CharType) * (ms_BUFFER_SIZE + 1));
#if GFM_PLATFORM_WINDOWS
	m_ptr = str;
	m_length = detail::CStringHelper::Len(m_ptr);
	m_ptrInitialized = true;
#else
	m_length = detail::CStringHelper::Len(str);
	if(m_length <= ms_BUFFER_SIZE) {
		detail::CStringHelper::Convert(str, m_buffer, ms_BUFFER_SIZE + 1);
		m_ptrInitialized = false;
	}
	else {
		m_tempBuffer = static_cast<CharType*>(memory::DefaultAllocator::Allocate(m_length + 1));
		detail::CStringHelper::Convert(str, m_tempBuffer.Raw(), m_length);
		m_ptr = m_tempBuffer.Raw();
		m_ptrInitialized = true;
	}
#endif
}

gfm::String::FormatVarArg::FormatVarArg(wchar_t ch) : m_length(1), m_ptrInitialized(false),
m_tempBuffer(nullptr) {
	memset(m_buffer, 0, sizeof(CharType) * (ms_BUFFER_SIZE + 1));
#if GFM_PLATFORM_WINDOWS
	m_buffer[0] = ch;
#else
	detail::CStringHelper::Convert(&ch, m_buffer, 1);
#endif
	m_buffer[1] = '\0';
}

gfm::String::FormatVarArg::FormatVarArg(char ch) : m_length(1), m_ptrInitialized(false),
m_tempBuffer(nullptr) {
	memset(m_buffer, 0, sizeof(CharType) * (ms_BUFFER_SIZE + 1));
#if GFM_PLATFORM_WINDOWS
	detail::CStringHelper::Convert(&ch, m_buffer, 1);
#else
	m_buffer[0] = ch;
#endif
	m_buffer[1] = '\0';
}
gfm::String::FormatVarArg::FormatVarArg(const String& value) : 
m_length(value.Length()), m_ptrInitialized(true), m_tempBuffer(nullptr) {
	memset(m_buffer, 0, sizeof(CharType) * (ms_BUFFER_SIZE + 1));
	m_ptr = value.CStr();
	m_ptrInitialized = true;
}
gfm::String::FormatVarArg::FormatVarArg(const std::string& value) :
m_tempBuffer(nullptr) {
	memset(m_buffer, 0, sizeof(CharType) * (ms_BUFFER_SIZE + 1));
#if GFM_PLATFORM_WINDOWS
	m_length = detail::CStringHelper::Convert(value.c_str(), m_buffer, ms_BUFFER_SIZE);
	m_ptrInitialized = false;
#else
	m_ptr = str;
	m_length = value.length();
	m_ptrInitialized = true;
#endif
}
gfm::String::FormatVarArg::FormatVarArg(const std::wstring& value) :
m_tempBuffer(nullptr) {
	memset(m_buffer, 0, sizeof(CharType) * (ms_BUFFER_SIZE + 1));
#if GFM_PLATFORM_WINDOWS
	m_ptr = value.c_str();
	m_length = value.length();
	m_ptrInitialized = true;
#else
	m_length = detail::CStringHelper::Convert(value, m_buffer, ms_BUFFER_SIZE);
	m_ptrInitialized = false;
#endif
}

gfm::String::SizeType gfm::String::FormatVarArg::Length() const noexcept {
	return m_length;
}
const gfm::String::CharType* gfm::String::FormatVarArg::CStr() const noexcept {
	return (m_ptrInitialized) ? m_ptr : m_buffer;
}

template<typename SkalarType, typename Dummy = typename std::enable_if
	<std::is_integral<SkalarType>::value || std::is_floating_point<SkalarType>::value>::type>
gfm::String::FormatVarArg::FormatVarArg(SkalarType skalar) {
	m_length = detail::CStringHelper::Snprintf(m_buffer, ms_BUFFER_SIZE, detail::TypeToFormatChar<SkalarType, CharType>::value, skalar);
	m_ptrInitialized = false;
}

template gfm::String::FormatVarArg::FormatVarArg(unsigned char skalar);
template gfm::String::FormatVarArg::FormatVarArg(short skalar);
template gfm::String::FormatVarArg::FormatVarArg(unsigned short skalar);
template gfm::String::FormatVarArg::FormatVarArg(int skalar);
template gfm::String::FormatVarArg::FormatVarArg(unsigned int skalar);
template gfm::String::FormatVarArg::FormatVarArg(long skalar);
template gfm::String::FormatVarArg::FormatVarArg(unsigned long skalar);
template gfm::String::FormatVarArg::FormatVarArg(long long skalar);
template gfm::String::FormatVarArg::FormatVarArg(unsigned long long skalar);
template gfm::String::FormatVarArg::FormatVarArg(float skalar);
template gfm::String::FormatVarArg::FormatVarArg(double skalar);
template gfm::String::FormatVarArg::FormatVarArg(long double skalar);