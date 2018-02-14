#pragma once
#include <stdexcept>
#include <utility>
#include <stdio.h>
#include <ctype.h>
#include "../../../Macro/BestInline.h"
#include "../../../Macro/Platform.h"
#include "../../../Utils/Types.h"


namespace gfm 
{
namespace detail 
{

	struct CStringHelper final 
	{
#if GFM_PLATFORM_WINDOWS
		using CharType = wchar_t;
#else
		using CharType = char;
#endif
		using SizeType = utils::uint32;

		static GFM_BEST_INLINE float ToFloat(const char* str) {
			return static_cast<float>(std::strtof(str, nullptr));
		}

		static GFM_BEST_INLINE float ToFloat(const wchar_t* str) {
			return static_cast<float>(::wcstof(str, nullptr));
		}

		static GFM_BEST_INLINE double ToDouble(const char* str) {
			return std::atof(str);
		}

		static GFM_BEST_INLINE double ToDouble(const wchar_t* str) {
			return ::_wtof(str);
		}

		static GFM_BEST_INLINE int ToInt(const char* str) {
			return std::atoi(str);
		}

		static GFM_BEST_INLINE int ToInt(const wchar_t* str) {
			return ::_wtoi(str);
		}

		static GFM_BEST_INLINE unsigned int ToUInt(const char* str) {
			return std::strtoul(str, nullptr, 0);
		}

		static GFM_BEST_INLINE unsigned int ToUInt(const wchar_t* str) {
			return std::wcstoul(str, nullptr, 0);
		}

		static GFM_BEST_INLINE long ToLong(const char* str) {
			return std::atoi(str);
		}

		static GFM_BEST_INLINE long ToLong(const wchar_t* str) {
			return ::_wtoi(str);
		}

		static GFM_BEST_INLINE unsigned long ToULong(const char* str) {
			return std::strtoul(str, nullptr, 0);
		}

		static GFM_BEST_INLINE unsigned long ToULong(const wchar_t* str) {
			return std::wcstoul(str, nullptr, 0);
		}

		static GFM_BEST_INLINE long long ToLongLong(const char* str) {
			return std::strtoll(str, nullptr, 0);
		}

		static GFM_BEST_INLINE long long ToLongLong(const wchar_t* str) {
			return std::wcstoll(str, nullptr, 0);
		}

		static GFM_BEST_INLINE unsigned long long ToULongLong(const char* str) {
			return std::strtoull(str, nullptr, 0);
		}

		static GFM_BEST_INLINE unsigned long long ToULongLong(const wchar_t* str) {
			return std::wcstoull(str, nullptr, 0);
		}

		static GFM_BEST_INLINE decltype(auto) Convert(const wchar_t* in, char * out, SizeType count) {
			return std::wcstombs(out, in, count);
		}

		static GFM_BEST_INLINE decltype(auto) Convert(const char * in, wchar_t * out, SizeType count) {
			return std::mbstowcs(out, in, count);
		}

		static GFM_BEST_INLINE decltype(auto) Convert(const char* in, const char* out, SizeType size) {
			return size;
		}

		static GFM_BEST_INLINE decltype(auto) Convert(const wchar_t* in, const wchar_t* out, SizeType size) {
			return size;
		}

		static GFM_BEST_INLINE decltype(auto) Convert(wchar_t in, char& out) {
			std::wcstombs(&out, &in, 1);
		}

		static GFM_BEST_INLINE decltype(auto) Convert(char in, wchar_t& out) {
			std::mbstowcs(&out, &in, 1);
		}

		static GFM_BEST_INLINE decltype(auto) Copy(wchar_t* dest, const wchar_t* source, SizeType len) {
			return std::wmemcpy(dest, source, len +1);
		}

		static GFM_BEST_INLINE decltype(auto) Copy(char* dest, const char* source, SizeType len) {
			return std::memcpy(dest, source, len +1);
		}

		static GFM_BEST_INLINE decltype(auto) Copy(wchar_t* dest, const char* source, SizeType len) {
			return Convert(source, dest, len + 1);
		}

		static GFM_BEST_INLINE decltype(auto) Copy(char* dest, const wchar_t* source, SizeType len) {
			return Convert(source, dest, len + 1);
		}

		static GFM_BEST_INLINE decltype(auto) Len(const wchar_t* str) {
			return std::wcslen(str);
		}

		static GFM_BEST_INLINE decltype(auto) Len(const char* str) {
			return std::strlen(str);
		}

		static GFM_BEST_INLINE decltype(auto) Compare(const wchar_t* left, const wchar_t* right, SizeType len) {
			return std::wcsncmp(left, right, len);
		}

		static GFM_BEST_INLINE decltype(auto) Compare(const char* left, const char* right, SizeType len) {
			return std::strncmp(left, right, len);
		}

		template<typename... ArgumentPack>
		static GFM_BEST_INLINE decltype(auto) Format(wchar_t * buffer, SizeType size, const wchar_t* format, ArgumentPack&&... args) {
			return _snwprintf(buffer, size, format, std::forward<ArgumentPack&&>(args)...);
		}

		template<typename... ArgumentPack>
		static GFM_BEST_INLINE decltype(auto) Format(char * buffer, SizeType size, const char* format, ArgumentPack&&... args) {
			return std::snprintf(buffer, size, format, std::forward<ArgumentPack&&>(args)...);
		}

		static GFM_BEST_INLINE decltype(auto) IsSpace(wchar_t ch) {
			return ::iswspace(ch) || ch == 0;
		}

		static GFM_BEST_INLINE decltype(auto) IsSpace(char ch) {
			return ::isspace(ch) || ch == 0;
		}

		static GFM_BEST_INLINE decltype(auto) IsDigit(wchar_t ch) {
			return ::iswdigit(ch);
		}

		static GFM_BEST_INLINE decltype(auto) IsDigit(char ch) {
			return ::isdigit(ch);
		}

		static GFM_BEST_INLINE decltype(auto) ToUpper(wchar_t ch) {
			return towupper(ch);
		}

		static GFM_BEST_INLINE decltype(auto) ToUpper(char ch) {
			return toupper(ch);
		}

		static GFM_BEST_INLINE decltype(auto) ToLower(wchar_t ch) {
			return towlower(ch);
		}

		static GFM_BEST_INLINE decltype(auto) ToLower(char ch) {
			return tolower(ch);
		}
		
		static constexpr decltype(auto) CharToNumber(wchar_t ch) {
			CharToNumber(static_cast<char>(ch));
		}

		static constexpr decltype(auto) ToInt(const char* str, utils::uint32 len) {
			if (len == 1) {
				return CharToNumber(*str);
			}
			return ToInt(str);
		}


		static constexpr decltype(auto) ToInt(const wchar_t* str, utils::uint32 len) {
			if (len == 1) {
				return WCharToNumber(*str);
			}
			return ToInt(str);
		}

		template<typename... ArgPack>
		static constexpr decltype(auto) Snprintf(char*const buffer, SizeType bufferSize, const char* const format, ArgPack&&... arguments) {
			return std::snprintf(buffer, bufferSize, format, std::forward<ArgPack&&>(arguments)...);
		}

		template<typename... ArgPack>
		static constexpr decltype(auto) Snprintf(wchar_t*const buffer, SizeType bufferSize, const wchar_t* const format, ArgPack&&... arguments) {
			return std::swprintf(buffer, bufferSize, format, std::forward<ArgPack&&>(arguments)...);
 		}

		static constexpr utils::int32 WCharToNumber(wchar_t ch) {
			switch (ch) {
			case L'0': return 0;
			case L'1': return 1;
			case L'2': return 2;
			case L'3': return 3;
			case L'4': return 4;
			case L'5': return 5;
			case L'6': return 6;
			case L'7': return 7;
			case L'8': return 8;
			case L'9': return 9;
			default: throw std::invalid_argument("ch that was passed to WCharToNumber was not a DIGIT!");
			}
			return -1; // warning fix
		}

		static constexpr utils::int32 CharToNumber(char ch) {
			switch (ch) {
				case '0': return 0;
				case '1': return 1;
				case '2': return 2;
				case '3': return 3;
				case '4': return 4;
				case '5': return 5;
				case '6': return 6;
				case '7': return 7;
				case '8': return 8;
				case '9': return 9;
				default: throw std::invalid_argument("ch that was passed to CharToNumber was not a DIGIT!");
			}
			return -1; // warning fix
		}
	};
}// detail
}//gfm