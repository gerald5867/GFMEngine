#pragma once
#include <exception>
#include "../../../Policys/Anyable.h"
#include "../../../Utils/Types.h"
#include "../../../TypeTraits/Copy.h"
#include "../../../Memory/DefaultAllocator.h"
#include "../../../Utils/SaveRelease.h"
#include "TrivialContainer.h"


#define TRIVIAL_LIST_NAME List
#define SFINAE_DUMMY typename std::enable_if<std::is_trivial<ValueType>::value>::type
namespace gfm 
{
namespace detail
{
	template<typename ValueType, typename Allocator = memory::DefaultAllocator, typename Dummy = void>
	class TRIVIAL_LIST_NAME;

	template<typename ValueType, typename Allocator>
	class TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>
	final: public TrivialContainer<ValueType, Allocator>, 
		public policy::detail::Anyable<TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>, ValueType>
	{

	public:
		using SizeType = utils::uint32;
		using VType = ValueType;
		using Alloc = Allocator;
		static constexpr const bool ISTRIVIAL = true;

	public:
		~TRIVIAL_LIST_NAME() noexcept = default;
		TRIVIAL_LIST_NAME()           = default;
		TRIVIAL_LIST_NAME(TRIVIAL_LIST_NAME < ValueType, Allocator, SFINAE_DUMMY > &&)			     = default;
		TRIVIAL_LIST_NAME(const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>&)			     = default;
		TRIVIAL_LIST_NAME& operator = (const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>&) = default;
		TRIVIAL_LIST_NAME& operator = (TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>&&)	     = default;

		explicit TRIVIAL_LIST_NAME(SizeType valueCount);
		TRIVIAL_LIST_NAME(ValueType&& value, SizeType count);
		TRIVIAL_LIST_NAME(const std::initializer_list<ValueType>& initTrivialList);

		//LOOK AT C#
		//MAKE FUNCTIONS FOR TRIVIAL TrivialList 
		//operatoren

	public:
		GFM_BEST_INLINE ValueType&  Append(const ValueType& value);
		GFM_BEST_INLINE ValueType&  Append(const TRIVIAL_LIST_NAME < ValueType, Allocator, SFINAE_DUMMY> & other);
		GFM_BEST_INLINE ValueType&  Append(TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>&& other);
		void Append(const std::initializer_list<ValueType>& initList);

		template<typename... ValueTypes>
		void AppendRange(ValueTypes&&... values);

		template<typename... CtorArgPack>
		ValueType& AppendInPlace(CtorArgPack&&... arguments);

		GFM_BEST_INLINE decltype(auto) Insert(SizeType index, const ValueType& value);
		GFM_BEST_INLINE void Remove(SizeType index);

		template<typename ToType>
		void ConvertAll(TRIVIAL_LIST_NAME<ToType, Allocator, SFINAE_DUMMY>& outTrivialList) const;
		template<typename ToType>
		void ConvertAll(TRIVIAL_LIST_NAME<ToType, Allocator, SFINAE_DUMMY>& outTrivialList, SizeType startIndex) const;
		void CopyTo(ValueType* outPtr) const;
		void CopyTo(ValueType* outPtr, SizeType index) const;

		void ForEach(void(*predicate)(ValueType&));
		void ForEach(void(*predicate)(const ValueType&)) const;

		ValueType& PopLast();
		const ValueType& Last() const;
		ValueType& Last();

	public:
		GFM_BEST_INLINE ValueType* begin() noexcept ;
		GFM_BEST_INLINE const ValueType* cbegin() const noexcept ;
		GFM_BEST_INLINE ValueType* end() noexcept ;
		GFM_BEST_INLINE const ValueType* cend() const noexcept ;
		GFM_BEST_INLINE const ValueType* begin() const noexcept ;
		GFM_BEST_INLINE const ValueType* end() const noexcept ;
	public:
		//MAKE OVERLOADS FOR THE STL ALSO
		TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& operator += 
			(const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& other);
		TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& operator += 
			(const std::initializer_list<ValueType>& initList);
		TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& operator *= (SizeType Skalar);
		bool operator != (const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& other);
		bool operator == (const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& other);

#ifdef _MSC_VER
	#pragma region GlobalOperators
#endif
		friend TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY> operator +
		(const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& left, 
		 const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& right) {
			TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY> result;
			auto leftLen = left.Length();
			auto rightLen = right.Length();
			result.Reserve(leftLen + rightLen);
			std::memcpy(result.m_data, left.m_data, leftLen * sizeof(ValueType));
			std::memcpy(std::addressof(result.m_data[(result.m_size += leftLen)]), 
				right.m_data, rightLen * sizeof(ValueType));
			result.m_size += rightLen;
			return result;
		}

		friend TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY> operator +
		(const std::initializer_list<ValueType>& initListRight, 
		 const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& right) {
			TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY> result;
			auto initLen = initListRight.size();
			auto rightLen = right.Length();
			result.Reserve(initLen + rightLen);
			for (const auto& iter : initListRight) {
				result.m_data[m_size++] = iter;
			}
			std::memcpy(std::addressof(result.m_data[m_size]), right.m_data, rightLen * sizeof(ValueType));
			result.m_size += rightLen;
			return result;
		}

		friend TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY> operator +
		(const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& left, 
		const std::initializer_list<ValueType>& initListLeft) {
			TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY> result;
			auto initLen = initListLeft.size();
			auto leftLen = left.Length();
			result.Reserve(initLen + leftLen);
			std::memcpy(result.m_data, left.m_data, leftLen * sizeof(ValueType));
			result.m_size += leftLen;
			for (const auto& iter : initListLeft) {
				result.m_data[result.m_size++] = iter;
			}
			return result;
		}

		template<typename SkalarType>
		friend TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY> operator *
		(SkalarType skalar, const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& right) {
			typedef typename TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>::SizeType SizeType;
			TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY> result;
			if (skalar <= 0) {
				return result;
			}
			auto rightLen = right.Length();
			result.Reserve(rightLen * static_cast<SizeType>(skalar));
			for (SizeType i = 0; i < static_cast<SizeType>(skalar) * rightLen; i += rightLen) {
				std::memcpy(std::addressof(result.m_data[i]), right.m_data, rightLen * sizeof(ValueType));
			}
			result.m_size = skalar * rightLen;
			return result;
		}

		template<typename SkalarType>
		friend TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY> operator *
			(const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& left, SkalarType skalar) {
			auto result = skalar * left;
			return result;
		}
#ifdef _MSC_VER
	#pragma endregion GlobalOperators
#endif
	private:
		template<typename FirstType, typename... RestValueTypes>
		void UnrollAppendRange(FirstType&& firstArg, RestValueTypes&&... restArgs);
		template<typename LastType>
		void UnrollAppendRange(LastType&& lastArg);
	};
}//detail
}//gfm
#include "TrivialList.inl"
#undef TRIVIAL_LIST_NAME
#undef SFINAE_DUMMY