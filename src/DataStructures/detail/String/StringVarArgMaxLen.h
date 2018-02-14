#pragma once
#include "../../../Utils/Types.h"
namespace gfm 
{
namespace detail {
	template<typename T> struct VarArgCharLen { enum { value = 0 }; };

	template<> struct VarArgCharLen<utils::int8> { enum { value = 3 + 1 }; };
	template<> struct VarArgCharLen<utils::uint8> { enum { value = 3 }; };
	template<> struct VarArgCharLen<utils::int16> { enum { value = 5 + 1 }; };
	template<> struct VarArgCharLen<utils::uint16> { enum { value = 5 }; };
	template<> struct VarArgCharLen<utils::int32> { enum { value = 10 + 1 }; };
	template<> struct VarArgCharLen<utils::uint32> { enum { value = 10 }; };
	template<> struct VarArgCharLen<utils::int64> { enum { value = 20 + 1 }; };
	template<> struct VarArgCharLen<utils::uint64> { enum { value = 20 }; };
	template<> struct VarArgCharLen<float> { enum { value = sizeof(float) * 8 + 1 }; };
	template<> struct VarArgCharLen<double> { enum { value = sizeof(double) * 8 + 1 }; };
	template<> struct VarArgCharLen<long double> { enum { value = sizeof(long double) * 8 + 1 }; };
		
	template<typename... VarArgTypes>
	constexpr utils::uint32 MaxVarArgCharLen(VarArgTypes&&... arguments) noexcept {
		return(sizeof...(VarArgTypes) == 0) ? 0 : MaxVarArgCharLenIntern(std::forward<VarArgTypes&&>(arguments)...);
	}

	namespace {
		template<typename FirstType, typename... RestVarArgTypes>
		constexpr utils::uint32 MaxVarArgCharLenIntern(FirstType&& first, RestVarArgTypes&&... arguments) noexcept {
			static_cast<void>(first);
			return VarArgCharLen<FirstType>::value + MaxVarArgCharLenIntern(std::forward<RestVarArgTypes&&>(arguments)...);
		}

		template<typename LastType>
		static constexpr utils::uint32 MaxVarArgCharLenIntern(LastType&& last) noexcept {
			static_cast<void>(last);
			return  VarArgCharLen<LastType>::value;
		}
	}

}//detail
}//gfm