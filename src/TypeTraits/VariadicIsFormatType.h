#pragma once
#pragma once
#include <string>
#include <type_traits>
#include "../DataStructures/String.h"
namespace gfm {
	namespace traits {
		template <typename... Ts>
		struct AllFormatType;

		template <typename Head, typename... Tail>
		struct AllFormatType<Head, Tail...>
		{
			static const bool value = (std::is_floating_point<Head>::value || std::is_integral<Head>::value
				|| std::is_same<typename std::decay<Head>::type, String>:: value 
				|| std::is_same<typename std::decay<Head>::type, std::string>::value
				|| std::is_same<typename std::decay<Head>::type, std::wstring>::value
				|| std::is_same<typename std::remove_cv<typename std::remove_reference<Head>::type>::type, String>::value
				|| std::is_same<typename std::remove_cv<typename std::remove_reference<Head>::type>::type, std::string>::value
				|| std::is_same<typename std::remove_cv<typename std::remove_reference<Head>::type>::type, std::wstring>::value
				|| std::is_same<Head, const char*>::value
				|| std::is_same<Head, char*>::value
				|| std::is_same<Head, wchar_t*>::value
				|| std::is_same<Head, const char* const>::value
				|| std::is_same<Head, const wchar_t* const>::value
				|| std::is_same<Head, const wchar_t*>::value
				|| std::is_same<Head, wchar_t* const>::value
				|| std::is_same<Head, char* const>::value)
				&& AllFormatType<Tail...>::value;
		};

		template <typename LastT>
		struct AllFormatType<LastT>
		{
			static const bool value = (std::is_floating_point<LastT>::value || std::is_integral<LastT>::value
				|| std::is_same<typename std::decay<LastT>::type, String>::value
				|| std::is_same<typename std::decay<LastT>::type, std::string>::value
				|| std::is_same<typename std::decay<LastT>::type, std::wstring>::value
				|| std::is_same<typename std::remove_cv<typename std::remove_reference<LastT>::type>::type, String>::value
				|| std::is_same<typename std::remove_cv<typename std::remove_reference<LastT>::type>::type, std::string>::value
				|| std::is_same<typename std::remove_cv<typename std::remove_reference<LastT>::type>::type, std::wstring>::value
				|| std::is_same<LastT, const char*>::value
				|| std::is_same<LastT, char*>::value
				|| std::is_same<LastT, wchar_t*>::value
				|| std::is_same<LastT, const char* const>::value
				|| std::is_same<LastT, const wchar_t* const>::value
				|| std::is_same<LastT, const wchar_t*>::value
				|| std::is_same<LastT, wchar_t* const>::value
				|| std::is_same<LastT, char* const>::value);
		};
	}
}
#pragma once
