#pragma once
#include <type_traits>
#include <exception>
#include "../../../Utils/Types.h"
#include "../../../TypeTraits/Copy.h"
#include "../../../Memory/DefaultAllocator.h"
#include "../../../Utils/SaveRelease.h"
#include "ObjectContainer.h"

#define OBJECT_LIST List
#define SFINAE_DUMMY typename std::enable_if<!std::is_trivial<ValueType>::value>::type

namespace gfm
{
namespace detail
{
	template<typename ValueType, typename Allocator, typename Dummy> class OBJECT_LIST;
	template<typename ValueType, typename Allocator>
	class OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>
	final : public ObjectContainer<ValueType, Allocator>, 
		public policy::detail::Anyable<OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>, ValueType>
	{
	public:
		using SizeType = utils::uint32;
		using VType = ValueType;
		using Alloc = Allocator;
		static constexpr const bool ISTRIVIAL = false;

	public:
		OBJECT_LIST()		   = default;
		~OBJECT_LIST() noexcept = default;
		OBJECT_LIST& operator = (const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>&) = default;
		OBJECT_LIST& operator =(OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>&&)		 = default;
		OBJECT_LIST(const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>&)				 = default;
		OBJECT_LIST(OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>&&)					 = default;

		explicit OBJECT_LIST(SizeType valueCount);
		OBJECT_LIST(ValueType&& value, SizeType count);
		OBJECT_LIST(const std::initializer_list<ValueType>& initObjectList);

		//LOOK AT C#
		//MAKE FUNCTIONS FOR TRIVIAL ObjectList 
		//operatoren

	public:
		GFM_BEST_INLINE ValueType&  Append(ValueType&& value);
		GFM_BEST_INLINE ValueType&  Append(const ValueType& value);
		GFM_BEST_INLINE OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& Append(const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& other);
		GFM_BEST_INLINE OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& Append(OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>&& other);
		void Append(const std::initializer_list<ValueType>& initObjectList);

		template<typename... ValueTypes>
		void AppendRange(ValueTypes&&... values);

		template<typename... CtorArgPack>
		void AppendInPlace(CtorArgPack&&... arguments);

		GFM_BEST_INLINE decltype(auto) Insert(SizeType index, const ValueType& value);
		GFM_BEST_INLINE void Remove(SizeType index);

		template<typename ToType>
		void ConvertAll(OBJECT_LIST < ToType, Allocator, SFINAE_DUMMY > & outObjectList) const;
		template<typename ToType>
		void ConvertAll(OBJECT_LIST < ToType, Allocator, SFINAE_DUMMY > & outObjectList, SizeType startIndex) const;
		void CopyTo(ValueType* outPtr) const;
		void CopyTo(ValueType* outPtr, SizeType index) const;

		void ForEach(void(*predicate)(ValueType&));
		void ForEach(void(*predicate)(const ValueType&)) const;

		void PopLast();
		const ValueType& Last() const;
		ValueType& Last();

	public:
		GFM_BEST_INLINE ValueType* begin() noexcept override;
		GFM_BEST_INLINE const ValueType* cbegin() const noexcept override;
		GFM_BEST_INLINE ValueType* end() noexcept override;
		GFM_BEST_INLINE const ValueType* cend() const noexcept override;
		GFM_BEST_INLINE const ValueType* end() const noexcept override;
		GFM_BEST_INLINE const ValueType* begin() const noexcept override;
	public:
		OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& operator += (const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& other);
		OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& operator += (const std::initializer_list<ValueType>& initList);
		OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& operator *= (SizeType Skalar);
		bool operator != (const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& other);
		bool operator == (const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& other);

#ifdef _MSC_VER
	#pragma region GlobalOperators
#endif
		friend OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY> operator +
		(const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& left, const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& right) {
			typedef typename OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>::SizeType SizeType;
			OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY> result;
			auto leftLen = left.Length();
			auto rightLen = right.Length();
			result.Reserve(leftLen + rightLen);
			SizeType i = 0;
			for (;i < leftLen; ++i) {
				new (std::addressof(result.m_data[i])) ValueType(left.m_data[i]);
			}
			for (; i < rightLen; ++i) {
				new (std::addressof(result.m_data[i])) ValueType(right.m_data[i - leftLen]);
			}
			result.m_size = leftLen + rightLen;
			return result;
		}

		friend OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY> operator +
		(const std::initializer_list<ValueType>& initListRight, const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& right) {
			typedef typename OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>::SizeType SizeType;
			auto initLen = initListRight.size();
			auto rightLen = right.Length();
			ObjectList < ValueType, Allocator> result;
			result.Reserve(initLen + rightLen);
			for (const auto& iter : initListRight) {
				new (std::addressof(result.m_data[result.m_size++])) ValueType(iter);
			}
			for (SizeType i = 0; i < rightLen; ++i) {
				new (std::addressof(result.m_data[result.m_size++])) ValueType(right.m_data[i]);
			}
			return result;
		}

		friend OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY> operator +
		(const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& left, const std::initializer_list<ValueType>& initListRight) {
			typedef typename OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>::SizeType SizeType;
			bjectList<ValueType, Allocator> result;
			auto leftLen = left.Length();
			auto initLen = initListRight.size();
			result.Reserve(leftLen + initLen);
			for (SizeType i = 0; i < leftLen; ++i) {
				new (std::addressof(result.m_data[i])) ValueType(left[i])
			}
			result.m_length = leftLen;
			for (const auto& iter : initListRight) {
				new (std::addressof(result.m_data[m_size++])) ValueType(iter);
			}
			return result;
		}

		template<typename SkalarType>
		friend OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY> operator *
		(SkalarType skalar, const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& right) {
			typedef typename OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>::SizeType SizeType;
			OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY> result;
			auto rightLen = right.Length();
			if (skalar <= 0) {
				return result;
			}
			SizeType newSize = static_cast<SizeType>(skalar) * rightLen;
			result.Reserve(newSize);
			SizeType i = 0;
			do {
				for (i = 0; i < rightLen; i++) {
					new (std::addressof(result.m_data[result.m_size++])) ValueType(right.m_data[i]);
				}
			} while (result.m_size < newSize);
		}

		template<typename SkalarType>
		friend OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY> operator *
		(const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY> left, SkalarType skalar) {
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
}
}
#include "ObjectList.inl"
#undef SFINAE_DUMMY
#undef OBJECT_LIST