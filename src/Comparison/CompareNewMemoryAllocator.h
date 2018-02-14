#pragma once
#include <iostream>
#include <chrono>
#include "../Memory/MemoryAllocator.h"
#include "../Macro/BestInline.h"
namespace gfm {
	GFM_BEST_INLINE void compareMemoryAllocatorToNewAndDelete() {
		using namespace gfm;
		using namespace memory;
		auto before = std::chrono::high_resolution_clock::now();
		MemoryAllocator::initialize();
		for (int i = 0; i < 2535; i++) {
			auto * t = ::operator new[](i);
			::operator delete[](t);
		}
		auto after = std::chrono::high_resolution_clock::now();
		std::cout << "New and Delete Time :" << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << std::endl;
		
		before = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 2535; i++) {
			auto * t = MemoryAllocator::instance().NewMemory(i);
			MemoryAllocator::instance().DeleteMemory(t);
		}
		after = std::chrono::high_resolution_clock::now();
		std::cout << " Memory Allocator " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << std::endl;

	}
}