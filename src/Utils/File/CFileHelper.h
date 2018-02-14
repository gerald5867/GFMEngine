#pragma once
#ifndef C_FILE_HELPER_H
#define C_FILE_HELPER_H
#include <stdio.h>
#include "../../Macro/BestInline.h"
namespace gfm {
namespace utils {
namespace file {
class CFileHelper final
{
	public:
	GFM_BEST_INLINE static decltype(auto) OpenFile(const wchar_t* filePath, const wchar_t* mode) {
		return ::_wfopen(filePath, mode);
	}

	GFM_BEST_INLINE static decltype(auto) OpenFile(const char* filePath, const char* mode) {
		return ::fopen(filePath, mode);
	}
};
}//file
}//utils
}//gfm
#endif // C_FILE_HELPER_H