#pragma once
#include "../Memory/DefaultAllocator.h"
#include "detail/List/TrivialList.h"
#include "detail/List/ObjectList.h"

namespace gfm 
{
	//todo make base class object
	//make operators templated and accept stl containers also
	
	template<typename ValueType, typename Allocator = memory::DefaultAllocator>
	using List = detail::List<ValueType, Allocator>;
}//namespace gfm