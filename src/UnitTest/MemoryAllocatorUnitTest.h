#pragma once
#include <string>
#include "../Memory/MemoryAllocator.h"
namespace gfm 
{
	class MemAllocatorUnitTests
	{
	public:
		static bool AllTests() {
			return AllocAndDeallocLoop()
				&& AllocateAndPlaceLoop()
				&& AllocateAndDeallocatePlaceLoop();
		}
		static bool AllocAndDeallocLoop() {
			using namespace memory;
			for (int i = 0; i < 65536U; i+= 10) {
				void * mem = MemoryAllocator::instance().NewMemory(i * 2);
				MemoryAllocator::instance().DeleteMemory(mem);
			}
			if (!MemoryAllocator::instance().AllBytesFree()) {
				__debugbreak();
				std::cout << "MEMORY LEAK IN MEMORY ALLOCATOR" << std::endl;
				return false;
			}
			return true;
		}

		static bool AllocateAndDeallocatePlaceLoop() {
			class TestClass {
			public:
				double m[1024];
				std::string st[5];
				int zz[500];
				char g[204];
			public:
				TestClass() {
					for (int i = 0; i < 5; i++) {
						st[i] = "PAPA";
					}
					memset(m, 0, sizeof(double) * 1024);
					memcpy(zz, m, sizeof(int) * 500);
					strncpy(g, st[0].data(), st[0].length());
				}
			};
			using namespace memory;
			for (int i = 0; i < 50000; ++i) {
				void * mem = MemoryAllocator::instance().NewMemory(sizeof(TestClass));
				new (mem) TestClass();
				MemoryAllocator::instance().DeleteMemory(mem);
			}
			if (!MemoryAllocator::instance().AllBytesFree()) {
				__debugbreak();
				std::cout << "MEMORY LEAK IN MEMORY ALLOCATOR" << std::endl;
				return false;
			}
			return true;
		}

		static bool AllocateAndPlaceLoop() {
			using namespace memory;
			class TestClass 
			{
			public:
				TestClass() : m(5.505), 
					z(50505), 
					g('a'), 
					f(true) {
					static constexpr const char testPtr[] = "HALLO MEIN NAME IST GERALD UND DAS IST DER UNIT TEST FUER DEN MEMORY ALLOCATOR";
					memcpy(t, testPtr, 79);
				}
				double m;
				int z;
				char g;
				bool f;
				char t[256];
			public:
				bool success(){
					static const char * testPtr = "HALLO MEIN NAME IST GERALD UND DAS IST DER UNIT TEST FUER DEN MEMORY ALLOCATOR";
					std::string left(testPtr);
					std::string right(t);
					return  m == 5.505 && z == 50505 && g == 'a' && f == true && left == right;
				
				}
			};
			for (int i = 0; i < 100000; i++) {
				void * mem = MemoryAllocator::instance().NewMemory(sizeof(TestClass));
				new (mem) TestClass();
				if (!reinterpret_cast<TestClass*>(mem)->success()) {
					__debugbreak();
				}
				MemoryAllocator::instance().DeleteMemory(mem);
			}
			if (!MemoryAllocator::instance().AllBytesFree()) {
				__debugbreak();
				std::cout << "MEMORY LEAK IN MEMORY ALLOCATOR" << std::endl;
				return false;
			}
			return true;
		}
	};

}// namespace gfm