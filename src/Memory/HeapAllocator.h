#pragma once
#include "../Macro/Debug.h"
#ifndef HEAP_ALLOCATOR_H
#define HEAP_ALLOCATOR_H

#if GFM_IS_DEBUG_MODE

#define new new(__FILE__, __LINE__)
#define delete delete(__FILE__, __LINE__)

#endif // GFM_IS_DEBUG_MODE

#endif // HEAP_ALLOCATOR_H
