#pragma once
#include "../Utils/Types.h"
#include "../DataStructures/List.h"
namespace gfm 
{
namespace algorithm 
{
	template<typename ReturnType = utils::int32, typename ToSumType>
	constexpr ReturnType Sum(const ToSumType* sumables, utils::uint32 sumablesLength, 
		ReturnType(*predicate)(const ToSumType&)) {
		ReturnType sum = 0;
		for (utils::uint32 i = 0; i < sumablesLength; ++i) {
			sum += predicate(sumables[i]);
		}
		return sum;
	}
	//TODO CHECK FOR += operator
	//TODO STATIC ASSERT FOR TYPES
	template<typename ReturnType = utils::int32, typename FirstSumType, typename SecondSumType, typename FirstSumTypeDecayed = 
		typename std::decay<FirstSumType>::type, typename SecondSumTypeDecayed = std::decay<SecondSumType>::type,
		typename Dummy = typename std::enable_if< (std::is_floating_point<FirstSumTypeDecayed>::value || 
		std::is_integral<FirstSumTypeDecayed>::value) && (std::is_floating_point<SecondSumTypeDecayed>::value ||
		std::is_integral<SecondSumTypeDecayed>::value)>::type,typename... RestSumTypes>
	constexpr ReturnType Sum(FirstSumType first, SecondSumType second, RestSumTypes... rest) {
		ReturnType sum = first + second;
		ReturnType restArgs[] = { static_cast<ReturnType>(rest)... };
		for (auto it : restArgs) {
			sum += it;
		}
		return sum;
	}

	template<typename ReturnType = utils::int32, typename SkalarPtr>
	constexpr ReturnType Sum(const SkalarPtr* sumArray, utils::uint32 size) {
		ReturnType sum = 0;
		for (auto i = 0U; i < size; ++i) {
			sum += sumArray[i];
		}
		return sum;
	}

	template<typename ReturnType = utils::int32, typename SkalarType, typename Allocator>
	ReturnType Sum(const List<SkalarType, Allocator>& lst) {
		ReturnType sum = 0;
		for (auto it : lst) {
			sum += static_cast<ReturnType>(it);
		}
		return sum;
	}

	template<typename ReturnType = utils::int32, typename SkalarType, typename Allocator>
	ReturnType Sum(const List<SkalarType, Allocator>& lst, ReturnType(*predicate)(const SkalarType&)) {
		ReturnType sum = 0;
		for (const auto& it : lst) {
			sum += predicate(it);
		}
		return sum;
	}
}
}