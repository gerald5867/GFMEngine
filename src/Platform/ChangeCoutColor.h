#pragma once
#include "../Macro/Platform.h"
#include "../Utils/Types.h"
#include "Windows/WINChangeCoutColor.h"
namespace gfm {
namespace utils {
	enum class ConsoleColor : utils::uint16 {
		eDEFAULT = 0x0007,
		eRED = 0x0004,
		eBLUE = 0x0001,
		eYELLOW = eBLUE | eRED,
		eGREEN = 0x0002,
		eLIGHT_RED = eRED | eGREEN
	};

	GFM_BEST_INLINE void ChangeCoutColor(ConsoleColor newColor) {
#if GFM_PLATFORM_WINDOWS
		windows::ChangeCoutColor(static_cast<utils::uint16>(newColor));
#elif GFM_PLATFORM_UNIX
		switch (newColor) {
		case eDEFAULT:unix::ChangeCoutColor("\033[0m");  break;
		case eRED:    unix::ChangeCoutColor("\033[31m"); break;
		case eBLUE:   unix::ChangeCoutColor("\033[34m"); break;
		case eYELLOW: unix::ChangeCoutColor("\033[33m"); break;
		case eGREEN:  unix::ChangeCoutColor("\033[32m"); break;
		}
#endif
	}
}//utils
}//gfm