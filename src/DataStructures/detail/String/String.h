#pragma once
#ifndef STRING_H
#define STRING_H

#include <limits>
#include <string>
#include <functional>
#include "../../../Memory/UniquePointer.h"
#include "../../../Policys/Anyable.h"
#include "../../List.h"
#include "../../../Macro/BestInline.h"
#include "../../../Utils/SaveRelease.h"
#include "../../../Memory/DefaultAllocator.h"
#include "../../../Utils/Types.h"
#include "CStringHelper.h"

#ifndef STRING_WITH_LITERAL
#	if GFM_PLATFORM_WINDOWS
#		define STRING_WITH_LITERAL(str) L#str
#	else
#		define STRING_WITH_LITERAL(str) #str
#	endif
#endif

#define FORMAT_BUFFER_SIZE (65535U)
namespace gfm
{
	class String final : public policy::detail::Anyable<String, 
		typename detail::CStringHelper::CharType>
	{
	public:
		typedef typename detail::CStringHelper::CharType CharType;
		typedef typename detail::CStringHelper::SizeType SizeType;

	private:
		class FormatVarArg final 
		{
		public:

			template<typename SkalarType, typename Dummy = typename std::enable_if
			<std::is_integral<SkalarType>::value || std::is_floating_point<SkalarType>::value>::type>
			FormatVarArg(SkalarType skalar);
			FormatVarArg(const char* str);
			FormatVarArg(const unsigned char* str);
			FormatVarArg(const wchar_t* str);
			FormatVarArg(wchar_t ch);
			FormatVarArg(char ch);
			FormatVarArg(const String& value);
			FormatVarArg(const std::string& value);
			FormatVarArg(const std::wstring& value);

		public:
			SizeType Length() const noexcept;
			const CharType* CStr() const noexcept;

		private: 
			static constexpr const SizeType ms_BUFFER_SIZE = 64;
			union 
			{
				const CharType* m_ptr;
				CharType m_buffer[ms_BUFFER_SIZE + 1];
			};
			SizeType m_length;
			bool	 m_ptrInitialized = false;
			memory::UniquePointer<CharType, memory::DefaultDestroyer> m_tempBuffer;
		};

	public:
		String();
		String(const char* str);
		String(const wchar_t* str);
		String(const char* str, SizeType length);
		String(const wchar_t* str, SizeType length);
		String(const String& other);
		String(String&& other);
		explicit String(const std::string& other);
		explicit String(const std::wstring& other);
		explicit String(char c);
		explicit String(wchar_t c);
		explicit String(utils::uint16 num);
		explicit String(utils::uint32 num);
		explicit String(utils::uint64 num);
		explicit String(utils::int16 num);
		explicit String(utils::int32 num);
		explicit String(utils::int64 num);
		explicit String(float num);
		explicit String(double num);

		template<typename Allocator>
		explicit String(const List<wchar_t, Allocator>& lst);
		template<typename Allocator>
		explicit String(const List<char, Allocator>& lst);
		template<typename Allocator>
		String(const List<wchar_t, Allocator>& lst, SizeType length);
		template<typename Allocator>
		String(const List<char, Allocator>& lst, SizeType length);

		template<template<typename, typename = std::allocator<wchar_t>> class Container> // STL CONTAINER
		explicit String(const Container<wchar_t>& stlContainer);
		template<template<typename, typename = std::allocator<char>> class Container> // STL CONTAINER
		explicit String(const Container<char>& stlContainer);
		template<template<typename, typename = std::allocator<wchar_t>> class Container> // STL CONTAINER
		String(const Container<wchar_t>& stlContainer, SizeType length);
		template<template<typename, typename = std::allocator<char>> class Container> // STL CONTAINER
		String(const Container<char>& stlContainer, SizeType length);

		~String() noexcept;

	public:
		String SubString(SizeType index) const;
		String SubString(SizeType index, SizeType length) const;

		String ToLower() const;
		String ToUpper() const;

		String Trim() const;
		String Trim(SizeType index) const;
		String Trim(const List<CharType>& ToTrimChars) const;

	public:
		void Reserve(SizeType size);
		void Resize(SizeType newSize);
		void Clear() noexcept;
		bool Contains(CharType ch) const;
		bool Contains(const String& other) const;
		//need more overloads

	public:
		GFM_BEST_INLINE CharType& Append(char ch) noexcept;
		GFM_BEST_INLINE CharType& Append(wchar_t ch) noexcept;
		String& Append(const String& other);
		String& Append(const std::string& other);
		String& Append(const std::wstring& other);
		String& Append(const char* str);
		String& Append(const wchar_t* str);
		String& Append(const gfm::List<char>& other);
		String& Append(const gfm::List<wchar_t>& other);

	public:
		String Replace(CharType from, CharType to) const;
		String Replace(const String& from, const String& to) const;

		List<String> Split(const gfm::List<CharType>& toSplitChars) const;
		List<String> Split(const gfm::List<CharType>& toSplitChars, SizeType maxSubStrings) const;
		List<String> Split(CharType delim) const;
		List<String> Split(const String& delim) const;

		void ForEach(void(*predicate)(CharType&));
		void ForEach(const std::function<void(CharType&)> predicate);

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4544)
		template<typename... ArgPackTypes, typename Dummy = typename std::enable_if<(sizeof...(ArgPackTypes) >= 1)>::type>
		static String Format(const CharType * format, ArgPackTypes&&... arguments);
		static String Format(const CharType* format);
#pragma warning(pop)
#endif//MSCVER
		template<typename... ArgPackTypes, typename Dummy = typename std::enable_if<(sizeof...(ArgPackTypes) >= 1)>::type>
		static void FormatBuffer(const CharType * format, String& result, ArgPackTypes&&... arguments);
		static void FormatBuffer(const CharType* format, String& result);
	public:
		bool EndsWith(const String& value) const;
		bool StartsWith(const String& value) const;
		bool StartsWith(const CharType* value) const;

		utils::int32 IndexOf(utils::uint32 toStartIndex, const String& value) const;
		utils::int32 IndexOf(const String& value) const;
		utils::int32 IndexOf(CharType ch) const;
		utils::int32 IndexOf(utils::uint32 toStartIndex, CharType ch) const;
		utils::int32 LastIndexOf(const String& value) const noexcept;
		utils::int32 LastIndexOf(CharType ch) const noexcept;

		void Insert(SizeType index, CharType ch);
		void Insert(SizeType index, const String& other);
		void Remove(SizeType index);
		void Remove(SizeType index, SizeType length);

		bool IsNumber() const noexcept;
		bool isFloatingPoint() const noexcept;
		void Join(const String& delimiter, const List<String>& toJoin);
		void Join(CharType delimiter, const List<CharType>& toJoins);
		void Join(CharType delimiter, const List<String>& toJoin);
		void Join(const String& delimiter, const List<CharType>& toJoin);

	public:

		utils::int32 ToInt() const;
		utils::uint32 ToUInt() const;
		utils::uint32 ToULong() const;
		utils::uint32 ToLong() const;
		utils::int64 ToLongLong() const;
		utils::uint64 ToULongLong() const;
		float ToFloat() const;
		double ToDouble() const;

	public:
		//operators
		String& operator =(const String& other);
		String& operator =(String&& other);
		String& operator =(const wchar_t* other);
		String& operator =(const char* other);
		CharType& operator[](SizeType index);
		const CharType& operator[](SizeType index) const;

		bool operator ==(const String& right) const;
		bool operator ==(const CharType* right) const;
		bool operator !=(const String& right) const;
		bool operator !=(const CharType* right) const;
		
		String& operator +=(const String& other);
		String& operator +=(const std::string& other);
		String& operator +=(const std::wstring& other);
		String& operator +=(const char* str);
		String& operator +=(const wchar_t* str);
		String& operator +=(const gfm::List<char>& other);
		String& operator +=(const gfm::List<wchar_t>& other);

		String& operator *=(SizeType skalar);
	public:
		friend GFM_BEST_INLINE std::ostream& operator << (std::ostream& os, const String& str);
		friend GFM_BEST_INLINE String operator +(const String& left, const String& right);
		friend GFM_BEST_INLINE String operator +(const char* str, const String& right);
		friend GFM_BEST_INLINE String operator +(const String& left, const char* str);
		friend GFM_BEST_INLINE String operator +(const wchar_t* str, const String& right);
		friend GFM_BEST_INLINE String operator +(const String& left, const wchar_t* str);
		friend GFM_BEST_INLINE String operator +(const String& left, const gfm::List<char>& other);
		friend GFM_BEST_INLINE String operator +(const String& left, const gfm::List<wchar_t>& other);
		friend GFM_BEST_INLINE String operator +(const gfm::List<char>& other, const String& right);
		friend GFM_BEST_INLINE String operator +(const gfm::List<wchar_t>& other, const String& right);
		friend GFM_BEST_INLINE String operator *(const String& left, SizeType skalar);
		friend GFM_BEST_INLINE String operator *(SizeType skalar, const String& right);

	public:
		GFM_BEST_INLINE const CharType* Raw() const noexcept;
		GFM_BEST_INLINE CharType * Raw() noexcept;
		GFM_BEST_INLINE const CharType* CStr() const noexcept;
		GFM_BEST_INLINE CharType* CStr() noexcept;
		GFM_BEST_INLINE SizeType Length() const noexcept;
		GFM_BEST_INLINE SizeType Capacity() const noexcept;
		GFM_BEST_INLINE bool Empty() const noexcept;
	public:
		//STL
		GFM_BEST_INLINE const CharType * cbegin() const noexcept override;
		GFM_BEST_INLINE const CharType * cend()   const noexcept override;
		GFM_BEST_INLINE const CharType * begin()  const noexcept override;
		GFM_BEST_INLINE const CharType * end()    const noexcept override;
		GFM_BEST_INLINE CharType * begin() noexcept override;
		GFM_BEST_INLINE CharType * end()   noexcept override;

	private:
		template<typename RawCharType>
		void AppendRawStr(const RawCharType* str, SizeType len);

	private:
		GFM_BEST_INLINE bool UsesSSO() const noexcept;
		GFM_BEST_INLINE void SetUseSSO() noexcept;
		GFM_BEST_INLINE void SetUseNoSSO() noexcept;
		GFM_BEST_INLINE void ZeroInitialize() noexcept;
		
		template<typename CharPtrType>
		void InitializeFromCharPtr(const CharPtrType* str, SizeType initLen = 0);
		String ChangeForEachAndCopy(void(*predicate)(CharType&, CharType)) const;
		void GrowIfToSmall(SizeType toGrowSize);
		void Grow(SizeType toGrowSize);
	private: 
		static const constexpr utils::int32 ms_SSOSIZE = std::numeric_limits<utils::uint64>::digits + 1;

		union
		{
			CharType* m_ptr;
			CharType  m_ssoArray[ms_SSOSIZE + 1]; // THE LAST ONE IS TO CHECK IF WE USE SSO 
		};//union
		memory::DefaultAllocator m_allocator;
		SizeType			     m_length   = 0;
		SizeType				 m_capacity = 0;
	};//class String

}//namespace gfm

#include "String.inl"
#endif // STRING_H