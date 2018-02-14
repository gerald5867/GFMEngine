#pragma once
#include "../Utils/Types.h"
#include <initializer_list>
#ifndef ARRAY_H
#define ARRAY_H
namespace gfm {

template<typename ValueType, utils::uint32 LENGTH>
class Array final
{
	public:
		typedef typename utils::uint32 SizeType;

	public:
		constexpr Array() = default;
		 ~Array() noexcept = default;
		 Array(const std::initializer_list<ValueType>& initList);

		template<utils::uint32 otherLENGTH>
		constexpr Array(const Array<ValueType, otherLENGTH>& other);
		
		template<utils::uint32 otherLENGTH>
		constexpr Array(Array<ValueType, otherLENGTH>&& other);


	public:
		constexpr SizeType Length() const noexcept;

		constexpr const ValueType& operator[](SizeType index) const;
		constexpr ValueType& operator[](SizeType index);

		template<utils::uint32 otherLENGTH>
		constexpr Array<ValueType, LENGTH>& operator=(const Array<ValueType, otherLENGTH>& other);

		template<utils::uint32 otherLENGTH>
		constexpr Array<ValueType, LENGTH>& operator=(Array<ValueType, otherLENGTH>&& other);

		constexpr Array<ValueType, LENGTH>& operator=(const std::initializer_list<ValueType>& initList);

		constexpr const ValueType* Raw() const noexcept;
		constexpr ValueType* Raw() noexcept;

	public:
		//STL
		constexpr const ValueType* begin() const noexcept;
		constexpr const ValueType* cbegin() const noexcept;
		constexpr ValueType* begin() noexcept;

		constexpr const ValueType* end() const noexcept;
		constexpr const ValueType* cend() const noexcept;
		constexpr ValueType* end() noexcept;
	private:
		ValueType m_data[LENGTH];
};

}//gfm
#include "Array.inl"
#endif// ARRAY_H