#pragma once
#ifndef ANYABLE_H
#define ANYABLE_H
#include "AbstractRangeBased.h"
#include <type_traits>

namespace gfm {
namespace policy {
namespace detail {
	template<typename ToAnyableType, typename ValueType>
	class Anyable : public AbstractRangeBased<ValueType>
	{
	private:
		using MyType = ValueType;
	public:
		template<typename CompareType>
		constexpr bool Any(CompareType&& val) const {
			//TODO MAKE TRAIT TO STATIC_ASSERT FOR EQUALS OPERATOR !
			for (const auto& it : *this) {
				if (static_cast<MyType&&>(val) == it) {
					return true;
				}
			}
			return false;
		}
	};
}//detail
}//policy
}//gfm
#endif // ANYABLE_H