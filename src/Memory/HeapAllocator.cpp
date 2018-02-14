#pragma once
#include "../Macro/Debug.h"
#include "../Macro/Assertions.h"
#include "../Utils/Logger.h"

#define GFM_MEMORY_ALIGMENT 16
#if 0//GFM_IS_DEBUG_MODE 

namespace gfm {
namespace memory {

struct HeapPointer {
	void* ptr;
	utils::uint32 size;
	utils::uint32 lineNumber;
	const char* filename;
};

namespace {
	static constexpr const utils::uint32 g_heapBufferStartLen = 1024;
	static constexpr const utils::uint32 g_cMAGICHEAPENDNUMBER = 12121212U;

	HeapPointer* g_heapAllocations = nullptr;
	utils::uint32 g_heapBufferLen = g_heapBufferStartLen;
	utils::uint32 g_lastAllocation = 0;
	
	void CheckHeapBufferSize() {
		if(g_heapAllocations == nullptr) {
			g_heapAllocations = reinterpret_cast<HeapPointer*>(_aligned_malloc(sizeof(HeapPointer) * g_heapBufferStartLen, GFM_MEMORY_ALIGMENT));
		}
		if(g_lastAllocation >= g_heapBufferLen - 1) {
			auto* temp = reinterpret_cast<HeapPointer*>((sizeof(HeapPointer) * g_heapBufferLen * 2));
			std::memcpy(temp, g_heapAllocations, sizeof(HeapPointer) * g_heapBufferLen);
			_aligned_free(g_heapAllocations);
			g_heapBufferLen *= 2;
		}
	}

	void CheckCorruptedHeap() {
		using namespace utils;
		for(auto i = 0U; i < g_lastAllocation; ++i) {
			auto allocSize = g_heapAllocations[i].size;
			auto ptr = reinterpret_cast<byte*>(g_heapAllocations[i].ptr);
			//if(*(reinterpret_cast<uint32*>(ptr + allocSize - sizeof(uint32) * 2)) != g_cMAGICHEAPENDNUMBER) {
			//	GFM_DEBUG_BREAK;
			//}
			//GFM_DEBUG_ASSERT(*(reinterpret_cast<uint32*>(ptr + allocSize - sizeof(uint32) * 2)) == g_cMAGICHEAPENDNUMBER,
			//	GFM_STRING("!!!!!!!!! HEAP CORRUPTION DETECTED !!!!!!!!!!\n"
			//	"allocatedSize was {0}\n"
			//	"fileName was {1}\n"
			//	"lineNumber was {2}\n"
			//	"ptr was {3}\n\n\n\n"), allocSize,
			//	((g_heapAllocations[i].filename) ? g_heapAllocations[i].filename : "NO INFO"),
			//	((g_heapAllocations[i].lineNumber) ? g_heapAllocations[i].lineNumber : -1),
			//	ptr)
		}
	}

	void DeallocateDebug(void* memory) {
		CheckCorruptedHeap();
		_aligned_free(memory);
	}

	void* AllocateDebug(utils::uint32 size, const char* file = nullptr, utils::uint32 line = 0) {
		return _aligned_malloc(size, GFM_MEMORY_ALIGMENT);
	#if 0
		using namespace gfm::memory;
		using namespace gfm::utils;
		CheckHeapBufferSize();
		byte* ptr = reinterpret_cast<byte*>(_aligned_malloc(size + (2 * sizeof(uint32)), GFM_MEMORY_ALIGMENT));
		*(reinterpret_cast<uint32*>((ptr + size - sizeof(uint32) * 2))) = gfm::memory::g_cMAGICHEAPENDNUMBER;
		*(reinterpret_cast<uint32*>((ptr + size - sizeof(uint32)))) = size;
		HeapPointer hptr;
		hptr.ptr = ptr;
		hptr.size = size;
		hptr.lineNumber = line;
		hptr.filename = file;
		CheckCorruptedHeap();
		g_heapAllocations[g_lastAllocation++] = hptr;
		return ptr;
	#endif
	}
}
}//memory
}//gfm

namespace {
using uint32 = gfm::utils::uint32;
using byte = gfm::utils::byte;
}

void* operator new(uint32 size) {
	return gfm::memory::AllocateDebug(size);
}

void* operator new(uint32 size, const char* file, uint32 line) {
	return gfm::memory::AllocateDebug(size, file, line);
}

void* operator new[](uint32 size) {
	return gfm::memory::AllocateDebug(size);
}

void* operator new[](uint32 size, const char* file, uint32 line) {
	return gfm::memory::AllocateDebug(size);
}

void operator delete(void* block) {
	gfm::memory::DeallocateDebug(block);
}

void operator delete(void* block, const char* file, uint32 line) {
	gfm::memory::DeallocateDebug(block);
}

void operator delete[](void* block) {
	gfm::memory::DeallocateDebug(block);
}

void operator delete[](void* block, const char* file, uint32 line) {
	gfm::memory::DeallocateDebug(block);
}


#endif // GFM_IS_DEBUG_MODE