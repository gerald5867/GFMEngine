#pragma once
#include <type_traits>
#include "../Utils/Types.h"
namespace gfm {
namespace algorithm {

template<typename T>
constexpr bool All(const T* values, utils::uint32 size, bool(*predicate)(const T&)) {
	for(auto i = 0U; i < size; ++i) {
		if(!predicate(values[i])) {
			return false;
		}
	}
	return true;
}

template<typename T>
constexpr bool All(const T* values, utils::uint32 size) {
	static_assert(std::is_convertible<bool, T>::value, "All Type isnt convertible to bool !");
	for(auto i = 0U; i < size; ++i) {
		if(!static_cast<bool>(values[i])) {
			return false;
		}
	}
	return true;
}

}//gfm
}//algorithm