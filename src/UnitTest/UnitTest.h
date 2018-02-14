#pragma once
#include <iostream>
#include "MemoryAllocatorUnitTest.h"

namespace gfm
{
	void RunAllUnitTests() {
		if (!MemAllocatorUnitTests::AllTests()) {
			std::cout << "MemoryAllocator Unit Test failed !!!!" << std::endl;
		}
		else {
			std::cout << "MemoryAllocator Unit Test was success" << std::endl;
		}
	}
}