#pragma once
#include "String.h"

gfm::String::String() : m_length(0), m_capacity(ms_SSOSIZE) {
	ZeroInitialize();
	SetUseSSO();
}

gfm::String::String(const char* str) {
	InitializeFromCharPtr(str);
}

gfm::String::String(const wchar_t* str) {
	InitializeFromCharPtr(str);
}

gfm::String::String(const char* str, SizeType length) {
	InitializeFromCharPtr(str, length);
}

gfm::String::String(const wchar_t* str, SizeType length) {
	InitializeFromCharPtr(str, length);
}

gfm::String::String(const String& other) {
	if (other.UsesSSO()) {
		InitializeFromCharPtr(other.m_ssoArray, other.m_length);
	}
	else {
		InitializeFromCharPtr(other.m_ptr, other.m_length);
	}
}

gfm::String::String(String&& other) {
	if (other.UsesSSO()) {
		InitializeFromCharPtr(other.m_ssoArray, other.m_length);
	}
	else {
		other.SetUseSSO();
		m_ptr = other.m_ptr;
		m_length = other.m_length;
		m_capacity = other.m_capacity;
		SetUseNoSSO();
		other.m_length = 0;
		other.m_capacity = 0;
		other.m_ptr = nullptr;
	}
}

gfm::String::String(const std::string& other) {
	InitializeFromCharPtr(other.data(), other.length());
}

gfm::String::String(const std::wstring& other) {
	InitializeFromCharPtr(other.data(), other.length());
}

gfm::String::String(char c) {
	m_length = 1;
	m_capacity = ms_SSOSIZE;
	detail::CStringHelper::Copy(m_ssoArray, &c, 1);
	SetUseSSO();
}

gfm::String::String(wchar_t c) {
	m_length = 1;
	m_capacity = ms_SSOSIZE;
	detail::CStringHelper::Copy(m_ssoArray, &c, 1);
	SetUseSSO();
}

gfm::String::String(utils::uint16 num) {
	m_length = detail::CStringHelper::Format(m_ssoArray, ms_SSOSIZE, STRING_WITH_LITERAL("%u"), num) - 2;
	m_capacity = ms_SSOSIZE;
	SetUseSSO();
}

gfm::String::String(utils::uint32 num) {
	m_length = detail::CStringHelper::Format(m_ssoArray, ms_SSOSIZE, STRING_WITH_LITERAL("%ul"), num) - 2;
	m_capacity = ms_SSOSIZE;
	SetUseSSO();
}
gfm::String::String(utils::uint64 num) {
	m_length = detail::CStringHelper::Format(m_ssoArray, ms_SSOSIZE, STRING_WITH_LITERAL("%ull"), num) - 2;
	m_capacity = ms_SSOSIZE;
	SetUseSSO();
}

gfm::String::String(utils::int16 num) {
	m_length = detail::CStringHelper::Format(m_ssoArray, ms_SSOSIZE, STRING_WITH_LITERAL("%d"), num) - 2;
	m_capacity = ms_SSOSIZE;
	SetUseSSO();
}

gfm::String::String(utils::int32 num) {
	m_length = detail::CStringHelper::Format(m_ssoArray, ms_SSOSIZE, STRING_WITH_LITERAL("%ld"), num) - 2;
	m_capacity = ms_SSOSIZE;
	SetUseSSO();
}
gfm::String::String(utils::int64 num) {
	m_length = detail::CStringHelper::Format(m_ssoArray, ms_SSOSIZE, STRING_WITH_LITERAL("%lld"), num) - 2;
	m_capacity = ms_SSOSIZE;
	SetUseSSO();
}
gfm::String::String(float num) {
	m_length = detail::CStringHelper::Format(m_ssoArray, ms_SSOSIZE, STRING_WITH_LITERAL("%f"), num) - 2;
	m_capacity = ms_SSOSIZE;
	SetUseSSO();
}
gfm::String::String(double num) {
	m_length = detail::CStringHelper::Format(m_ssoArray, ms_SSOSIZE, STRING_WITH_LITERAL("%lf"), num) - 2;
	m_capacity = ms_SSOSIZE;
	SetUseSSO();
}

gfm::String::~String() noexcept {
	if (!UsesSSO() && m_ptr != nullptr) {
		m_allocator.Deallocate(m_ptr);
		m_ptr = nullptr;
	}
}