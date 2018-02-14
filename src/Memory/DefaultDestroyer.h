#pragma once
#include "../Macro/BestInline.h"
#ifndef DEFAULT_DESTROYER_H
#define DEFAULT_DESTROYER_H
namespace gfm {
namespace memory {

class DefaultDestroyer final {
	public:
	template<typename T>
	GFM_BEST_INLINE void static Destroy(T* dptr) {
		::operator delete[](dptr);
	}
};

class ObjectDestroyer final {
	public:
	template<typename T>
	GFM_BEST_INLINE void static Destroy(T* dptr) {
		::delete dptr;
	}
};

class ObjectArrayDestroyer final {
	public:
		template<typename T>
		GFM_BEST_INLINE void static Destroy(T* dptr) {
			::delete[] dptr;
		}
};

}//memory
}//gfm
#endif // DEFAULT_DESTROYER_H