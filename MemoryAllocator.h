#pragma once
#include "Single"
#define MEMORY_ALLOCATOR_PTR_ARRAY_SIZE 8192
namespace gfm 
{
namespace memory
{
	class MemoryAllocator final : 
	{
	public:
		MemoryAllocator(const MemoryAllocator &)			  = delete;
		MemoryAllocator(MemoryAllocator &&)				      = delete;
		MemoryAllocator& operator = (const MemoryAllocator &) = delete;
		MemoryAllocator& operator = (MemoryAllocator &&)	  = delete;
	
	private:
		void * m_usedPtr[MEMORY_ALLOCATOR_PTR_ARRAY_SIZE];
	};

}//namespace gfm
}//namespace memory