#pragma once
#include "../Utils/Types.h"
#include "../Policys/Singleton.h"
#define MEMORY_ALLOCATOR_PTR_ARRAY_SIZE 8192U
#define MEMORY_ALLOCATOR_CHUNK_SIZE 65536U
#define MEMORY_ALLOCATOR_USED_PTR_CHUNK_SIZE 1024

namespace gfm 
{
namespace memory
{
	class MemoryAllocator final : public policy::MakeSingletonPtr<MemoryAllocator>
	{
	private:
		struct AllocatorLinkedPtr
		{
			utils::uint32 poolIndex = 0;
			utils::uint32 size	    = 0;
			bool          inUse = false;
			utils::byte * poolPtr = nullptr;
		};
		struct MemoryPoolPtr 
		{
			utils::uint32 poolSize = 0;
			utils::byte * poolPtr = nullptr;
		};

	public:
		static void initialize();
		MemoryAllocator(const MemoryAllocator &)			  = delete;
		MemoryAllocator(MemoryAllocator &&)				      = delete;
		MemoryAllocator& operator = (const MemoryAllocator &) = delete;
		MemoryAllocator& operator = (MemoryAllocator &&)	  = delete;

	public:
		void * NewMemory(utils::uint32 size);
		void DeleteMemory(void * memory);
		bool AllBytesFree() const;
		
	private:
		MemoryAllocator();
		bool ActiveChunkToSmall(utils::uint32 requestedSize) const noexcept;
		void AllocateNewChunk(utils::uint32 size = MEMORY_ALLOCATOR_CHUNK_SIZE);
		AllocatorLinkedPtr * FindFreeMemory(utils::uint32 size) const;

		void InsertMemoryPoolPtr(utils::uint32 size);
		utils::uint32 SearchUsedPtrLocation(utils::uint32 size, utils::uint32 low, utils::uint32 high) const;

		void GrowUsedPtrArray();
		void GrowPoolArray();
	private:
		AllocatorLinkedPtr * m_usedPtrs = nullptr;
		utils::uint32	     m_usedPtrIndex = 0;

		utils::uint32  m_poolCount = 0;
		MemoryPoolPtr * m_memoryPools = nullptr;
		MemoryPoolPtr m_activeMemoryPool;
		MemoryPoolPtr m_ActiveHead;
	};

}//namespace gfm
}//namespace memory