#pragma once

namespace gfm
{
namespace detail 
{
	template<typename CharType, CharType... chs>
	struct CompileTimeString
	{
		static constexpr char str[sizeof...(chs)+1] = { chs..., '\0' };
	};
	
	template<typename FType, typename CharType> struct TypeToFormatChar {};
	template<typename str> struct TypeToFormatChar<str, char>{ static constexpr const char* value = "%s"; };
	template<> struct TypeToFormatChar<char, char> { static constexpr const char* value = "%c"; };
	template<> struct TypeToFormatChar<unsigned char, char> { static constexpr const char* value = "%cu"; };
	template<> struct TypeToFormatChar<short, char> { static constexpr const char* value = "%d"; };
	template<> struct TypeToFormatChar<unsigned short, char> { static constexpr const char* value = "%u"; };
	template<> struct TypeToFormatChar<int, char> { static constexpr const char* value = "%d"; };
	template<> struct TypeToFormatChar<unsigned int, char> { static constexpr const char* value = "%u"; };
	template<> struct TypeToFormatChar<long, char> { static constexpr const char* value = "%ld"; };
	template<> struct TypeToFormatChar<unsigned long, char> { static constexpr const char* value = "%lu"; };
	template<> struct TypeToFormatChar<long long, char> { static constexpr const char* value = "%lld"; };
	template<> struct TypeToFormatChar<unsigned long long, char> { static constexpr const char* value = "%llu"; };
	template<> struct TypeToFormatChar<float, char> { static constexpr const char* value = "%f"; };
	template<> struct TypeToFormatChar<double, char> { static constexpr const char* value = "%f"; };
	template<> struct TypeToFormatChar<long double, char> { static constexpr const char* value = "%f"; };

	template<typename str> struct TypeToFormatChar<str, wchar_t> { static constexpr const wchar_t* value = L"%s"; };
	template<> struct TypeToFormatChar<char, wchar_t> { static constexpr const wchar_t* value = L"%c"; };
	template<> struct TypeToFormatChar<unsigned char, wchar_t> { static constexpr const wchar_t* value = L"%cu"; };
	template<> struct TypeToFormatChar<short, wchar_t> { static constexpr const wchar_t* value = L"%d"; };
	template<> struct TypeToFormatChar<unsigned short, wchar_t> { static constexpr const wchar_t* value = L"%u"; };
	template<> struct TypeToFormatChar<int, wchar_t> { static constexpr const wchar_t* value = L"%d"; };
	template<> struct TypeToFormatChar<unsigned int, wchar_t> { static constexpr const wchar_t* value = L"%u"; };
	template<> struct TypeToFormatChar<long, wchar_t> { static constexpr const wchar_t* value = L"%ld"; };
	template<> struct TypeToFormatChar<unsigned long, wchar_t> { static constexpr const wchar_t* value = L"%lu"; };
	template<> struct TypeToFormatChar<long long, wchar_t> { static constexpr const wchar_t* value = L"%lld"; };
	template<> struct TypeToFormatChar<unsigned long long, wchar_t> { static constexpr const wchar_t* value = L"%llu"; };
	template<> struct TypeToFormatChar<float, wchar_t> { static constexpr const wchar_t* value = L"%f"; };
	template<> struct TypeToFormatChar<double, wchar_t> { static constexpr const wchar_t* value = L"%f"; };
	template<> struct TypeToFormatChar<long double, wchar_t> { static constexpr const wchar_t* value = L"%f"; };

	template< typename FirstArgPackType, typename... RestArgPackTypes>
	constexpr void CreateFormaterArray(const char ** formatBuffer, utils::uint32 index, 
		FirstArgPackType&& first, RestArgPackTypes&&... restArguments) {
		formatBuffer[index] = TypeToFormatChar<FirstArgPackType>::value;
		CreateFormaterArray<RestArgPackTypes...>(formatBuffer, ++index, std::forward<RestArgPackTypes&&>(restArguments)...);
	}

	template<typename LastArgPackType>
	constexpr void CreateFormaterArray(const char ** formatBuffer, utils::uint32 index, LastArgPackType&& lastArg) {
		formatBuffer[index++] = TypeToFormatChar<LastArgPackType>::value;
	}

}//detail
}//gfm