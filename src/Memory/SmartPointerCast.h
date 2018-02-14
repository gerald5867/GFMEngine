#pragma once
#include "../#include"
#include "UniquePointer.h"
#ifndef SMART_POINTER_CAST_H
#define SMART_POINTER_CAST_H
namespace gfm {
namespace memory {
namespace smart_pointer_cast {

	template<typename ToType, typename FromType>
	GFM_BEST_INLINE decltype(auto) StaticCast(ToType to, FromType FROM) {

}

}//smart_pointer_cast
}//memory
}//gfm


#endif //SMART_POINTER_CAST_H