#pragma once
#include <iostream>
#include "UNIXChangeCoutColor.h"

void gfm::unix::ChangeCoutColor(const char* newColor) {
	static constexpr const char* const clearColor = "\033[2J";
	std::cout << clearColor;
	std::cout << newColor;
}