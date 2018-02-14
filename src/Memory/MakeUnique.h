#pragma once
#include "UniquePointer.h"
#include "DefaultDestroyer.h"
#include "DefaultAllocator.h"
#include <memory>
char* bla = std::make_unique<char[]>(500U).get();

namespace gfm {
namespace memory {

	template<typename T, typename ...CtorArgTypes, typename = std::enable_if<!std::is_array<T>::value>::type>
	UniquePointer<T, ObjectDestroyer> MakeUnique(CtorArgTypes &&...arguments) {
		return UniquePointer<T, ObjectDestroyer>(DefaultAllocator::AllocateObject<T>(std::forward<CtorArgTypes&&>(arguments)...));
	}

	template<typename T, typename ...CtorArgTypes>
	UniquePointer<T, ObjectArrayDestroyer> MakeUniqueArray(utils::uint32 count, CtorArgTypes &&...arguments) {
		return UniquePointer<T, ObjectArrayDestroyer>(DefaultAllocator::AllocateObjectArray<T>(std::forward<CtorArgTypes&&>(arguments)...));
	}
}//memory
}//gfm
