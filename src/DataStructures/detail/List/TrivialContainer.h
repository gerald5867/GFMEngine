#pragma once
#include <exception>
#include "../../../Utils/Types.h"
#include "../../../TypeTraits/Copy.h"
#include "../../../Memory/DefaultAllocator.h"
#include "../../../Utils/SaveRelease.h"

namespace gfm
{
namespace detail
{
	template<typename ValueType, typename Allocator = memory::DefaultAllocator>
	class TrivialContainer
	{

	public:
		using SizeType = utils::uint32;
		using InternType = ValueType;
		using InternLRef = ValueType&;
		using InternRRef = ValueType&&;
		using InternCRef = const ValueType&;

	protected:
		~TrivialContainer() noexcept;
		TrivialContainer();
		explicit TrivialContainer(SizeType valueCount);
		TrivialContainer(TrivialContainer<ValueType, Allocator>&& other);
		TrivialContainer(const TrivialContainer<ValueType, Allocator>& other);
		TrivialContainer(const ValueType& value, SizeType count);
		TrivialContainer(const std::initializer_list<ValueType>& initTrivialContainer);

	public:
		TrivialContainer<ValueType, Allocator>& operator = (const TrivialContainer<ValueType, Allocator>& other);
		TrivialContainer<ValueType, Allocator>& operator = (TrivialContainer<ValueType, Allocator>&& other);
		GFM_BEST_INLINE ValueType& operator[](SizeType index);
		GFM_BEST_INLINE const ValueType& operator[](SizeType index) const;

	public:
		GFM_BEST_INLINE SizeType Length() const noexcept;
		GFM_BEST_INLINE SizeType Capacity() const noexcept;

		GFM_BEST_INLINE ValueType* Raw() noexcept;
		GFM_BEST_INLINE const ValueType* Raw() const noexcept;

		void Clear() noexcept;
		void Resize(SizeType size);
		void Reserve(SizeType size);
		GFM_BEST_INLINE bool Empty() const noexcept;
		bool Contains(const ValueType& val) const;

	protected:
		GFM_BEST_INLINE void GrowIfToSmall(SizeType toAddCount);
		GFM_BEST_INLINE void CopyDataTo(ValueType* newPtr);
		bool Equals(const TrivialContainer<ValueType, Allocator>& other);

	protected:

		SizeType   m_capacity = 0;
		SizeType   m_size = 0;
		mutable ValueType* m_data = nullptr;
		Allocator  m_allocator;
	};
}//detail
}//gfm
#include "TrivialContainer.inl"
