#pragma once
#include <utility>
#include <type_traits>
#include "../Utils/Types.h"
namespace gfm 
{
namespace traits 
{
	template<typename FromType, typename ToType,bool trivial = std::is_trivially_copyable<FromType>::value && 
		std::is_trivially_copyable<ToType>::value>
	constexpr decltype(auto) Copy(const FromType* from, ToType* to, utils::uint32 count, bool usePlacementNew) { 
		(trivial) ? detail::TrivialCopy<FromType, ToType>(from, to, count) : 
			detail::LoopCopy<FromType, ToType>(from, to, count, usePlacementNew);
	}

namespace detail 
{

	template<typename FromType, typename ToType>
	static constexpr decltype(auto) TrivialCopy(const FromType* from, ToType* to, utils::uint32 count) {
		std::memcpy(to, from, count * sizeof(FromType));
	}

	template<typename FromType, typename ToType>
	static constexpr decltype(auto) LoopCopy(const FromType* from, ToType* to, utils::uint32 count, bool usePlacementNew) {
		if (usePlacementNew) {
			for (utils::uint32 i = 0; i < count; i++) {
				to[i] = from[i];
			}
		}
		else {
			for (utils::uint32 i = 0; i < count; i++) {
				new (std::addressof(to[i])) ToType(from[i]);
			}
		}
	}
}// namepsace detail
}// namesace traits
}//namespace gfm