#pragma once
#include "../Macro/Platform.h"
#ifndef _MSC_VER
	#include <stdint.h>
#endif

namespace gfm
{
namespace utils
{
#if GFM_PLATFORM_WINDOWS
	using CharType = wchar_t;
#else 
	using CharType = char;
#endif

#ifdef _MSC_VER
	using uint64 = unsigned __int64;
	using int64 = __int64;
	using uint32 = unsigned __int32;
	using int32 = __int32;
	using uint16 = unsigned __int16;
	using int16 = __int16;
	using uint8 = unsigned __int8;
	using int8 = __int8;
	using byte = uint8;
#else
	using uint64 = uint64_t;
	using int64 = int64_t;
	using uint32 = uint32_t;
	using int32 = int32_t;
	using uint16 = uint16_t;
	using int16 = int16_t;
	using uint8 = uint8_t;
	using int8 = int8_t;
	using byte = uint8;
#endif
}
}//namespace gfm