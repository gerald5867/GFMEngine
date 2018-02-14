#pragma once
#include <utility>
#include "../Utils/SaveRelease.h"
#include "MemoryAllocator.h"
#include "../Math/MathCalc.h"

//TODO GROW THE ARRAYS IF NEEDED

gfm::memory::MemoryAllocator* gfm::policy::MakeSingletonPtr<gfm::memory::MemoryAllocator>::mp_instance;

void gfm::memory::MemoryAllocator::initialize(){
	if (MemoryAllocator::mp_instance != nullptr) {
		return;
	}
	MemoryAllocator::mp_instance = new MemoryAllocator();
}

gfm::memory::MemoryAllocator::MemoryAllocator(){
	m_memoryPools = new MemoryPoolPtr[MEMORY_ALLOCATOR_PTR_ARRAY_SIZE];
	m_activeMemoryPool.poolPtr = reinterpret_cast<utils::byte*>(::operator new[](MEMORY_ALLOCATOR_CHUNK_SIZE));
	m_activeMemoryPool.poolSize = MEMORY_ALLOCATOR_CHUNK_SIZE;
	m_usedPtrs = new AllocatorLinkedPtr[MEMORY_ALLOCATOR_USED_PTR_CHUNK_SIZE];
	std::memset(m_memoryPools, 0, MEMORY_ALLOCATOR_PTR_ARRAY_SIZE * sizeof(MemoryPoolPtr));
	std::memset(m_usedPtrs, 0, MEMORY_ALLOCATOR_USED_PTR_CHUNK_SIZE * sizeof(AllocatorLinkedPtr));
	m_memoryPools[0].poolPtr = m_activeMemoryPool.poolPtr;
	m_memoryPools[0].poolSize = MEMORY_ALLOCATOR_CHUNK_SIZE;
	m_ActiveHead = m_activeMemoryPool;
}

bool gfm::memory::MemoryAllocator::ActiveChunkToSmall(utils::uint32 requestedSize) const noexcept {
	return m_ActiveHead.poolPtr + requestedSize >  m_activeMemoryPool.poolPtr + m_activeMemoryPool.poolSize;
}

void gfm::memory::MemoryAllocator::DeleteMemory(void * memory) {
	for (utils::uint32 i = 0; i < m_usedPtrIndex; ++i) {
		if (m_usedPtrs[i].poolPtr == memory) {
			m_usedPtrs[i].inUse = false;
		}
	}
}

gfm::memory::MemoryAllocator::AllocatorLinkedPtr * gfm::memory::MemoryAllocator::FindFreeMemory(utils::uint32 size) const {
	for (utils::uint32 i = 0; i < m_usedPtrIndex; ++i) {
		if (!m_usedPtrs[i].inUse && m_usedPtrs[i].size >= size) {
			return  &m_usedPtrs[i];
		}
	}
	return nullptr;
}

void gfm::memory::MemoryAllocator::GrowUsedPtrArray() {
	if (m_usedPtrIndex >= MEMORY_ALLOCATOR_USED_PTR_CHUNK_SIZE) {
		auto * newUsedPtr = new AllocatorLinkedPtr[m_usedPtrIndex * 2];
		utils::uint32 oldSize = m_usedPtrIndex * sizeof(AllocatorLinkedPtr);
		std::memcpy(newUsedPtr, m_usedPtrs, oldSize);
		delete[] m_usedPtrs;
		m_usedPtrs = newUsedPtr;
	}
}

void gfm::memory::MemoryAllocator::GrowPoolArray() {
	if (m_poolCount >= MEMORY_ALLOCATOR_PTR_ARRAY_SIZE) {
		auto * newPoolArray = new MemoryPoolPtr[m_poolCount * 2];
		std::memcpy(newPoolArray, m_memoryPools, m_poolCount * sizeof(MemoryPoolPtr));
		delete[] m_memoryPools;
		m_memoryPools = newPoolArray;
	}
}

void gfm::memory::MemoryAllocator::AllocateNewChunk(utils::uint32 size) {
	m_memoryPools[++m_poolCount].poolPtr = reinterpret_cast<utils::byte*>(::operator new[](size));
	m_memoryPools[m_poolCount].poolSize = size;
	m_ActiveHead.poolPtr = reinterpret_cast<utils::byte*>(&m_memoryPools[m_poolCount]);
	m_ActiveHead.poolSize = size;
	m_activeMemoryPool = m_ActiveHead;
}

bool gfm::memory::MemoryAllocator::AllBytesFree() const {
	for (utils::uint32 i = 0; i < m_usedPtrIndex; ++i) {
		if (m_usedPtrs[i].inUse) {
			return false;
		}
	}
	return true;
}

gfm::utils::uint32 gfm::memory::MemoryAllocator::SearchUsedPtrLocation(gfm::utils::uint32 size, gfm::utils::uint32 startIndex, gfm::utils::uint32 arraySize) const
{
	if (arraySize <= startIndex)
		return (size > m_usedPtrs[startIndex].size) ? (startIndex + 1) : startIndex;

	utils::uint32 middle = (startIndex + arraySize) / 2;
	if (size == m_usedPtrs[middle].size)
		return middle + 1;

	if (size > m_usedPtrs[middle].size)
		return SearchUsedPtrLocation(size, middle + 1, arraySize);

	return SearchUsedPtrLocation(size, startIndex, middle - 1);
}

void gfm::memory::MemoryAllocator::InsertMemoryPoolPtr(utils::uint32 size) {
	utils::byte * oldHead = m_ActiveHead.poolPtr;
	utils::uint32 index = SearchUsedPtrLocation(size, 0, m_usedPtrIndex);
	if (m_usedPtrIndex > index) {
		std::memmove(&m_usedPtrs[index] + sizeof(AllocatorLinkedPtr), &m_usedPtrs[index], (m_usedPtrIndex - index) * sizeof(AllocatorLinkedPtr));
	}
	m_usedPtrs[index].poolPtr = oldHead;
	m_usedPtrs[index].size = size;
	m_usedPtrs[index].inUse = true;
	m_usedPtrs[index].poolIndex = m_poolCount;
	++m_usedPtrIndex;
	m_ActiveHead.poolPtr = oldHead + size;
}

void * gfm::memory::MemoryAllocator::NewMemory(utils::uint32 size) {
	GrowUsedPtrArray();
	AllocatorLinkedPtr * freeChunkFromActiveChunk = FindFreeMemory(size);
	if (freeChunkFromActiveChunk != nullptr) {
		freeChunkFromActiveChunk->inUse = true;
		return freeChunkFromActiveChunk->poolPtr;
	}
	if (ActiveChunkToSmall(size)) {
		GrowPoolArray();
		AllocateNewChunk((size < MEMORY_ALLOCATOR_CHUNK_SIZE) ? MEMORY_ALLOCATOR_CHUNK_SIZE : size);
	}
	void * mem = m_ActiveHead.poolPtr;
	InsertMemoryPoolPtr(size);
	return mem;
}