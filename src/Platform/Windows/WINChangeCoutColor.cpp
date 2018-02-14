#pragma once
#include <windows.h>
#include "WINChangeCoutColor.h"

void gfm::windows::ChangeCoutColor(utils::uint16 newColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, newColor);
}