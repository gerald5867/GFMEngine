#pragma once
#include <type_traits>
namespace gfm {
	namespace traits {
		template <typename... Ts>
		struct AllFloatingPoint;

		template <typename Head, typename... Tail>
		struct AllFloatingPoint<Head, Tail...>
		{
			static const bool value = std::is_floating_point<Head>::value && AllFloatingPoint<Tail...>::value;
		};

		template <typename T>
		struct AllFloatingPoint<T>
		{
			static const bool value = std::is_floating_point<T>::value;
		};
	}
}
#pragma once
