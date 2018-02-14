#pragma once
#include "../Macro/BestInline.h"
namespace gfm 
{
namespace utils
{
	template<typename PointerType>
	GFM_BEST_INLINE void SaveRelease(PointerType * ptr) noexcept{
		if (ptr != nullptr) {
			delete ptr;
			ptr = nullptr;
		}
	}

	template<typename PointerType>
	GFM_BEST_INLINE void SaveReleaseArray(PointerType * ptr) noexcept {
		if (ptr != nullptr) {
			delete[] ptr;
			ptr = nullptr;
		}
	}
}//namespace utils
}//namespace gfm