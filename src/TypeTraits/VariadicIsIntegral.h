#pragma once
#include <type_traits>
namespace gfm {
	namespace traits {
		template <typename... Ts>
		struct AllIntegral;

		template <typename Head, typename... Tail>
		struct AllIntegral<Head, Tail...>
		{
			static const bool value = std::is_integral<Head>::value && AllIntegral<Tail...>::value;
		};

		template <typename T>
		struct AllIntegral<T>
		{
			static const bool value = std::is_integral<T>::value;
		};
	}
}
