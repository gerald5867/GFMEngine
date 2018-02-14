#include "FileOpenMode.h"
#include "../Types.h"

const char* gfm::utils::file::ModeTypeToString(FileOpenMode mode) noexcept {
	static constexpr const char* const modes[] = {
		"w", "r", "r+", "w+", "a+", "wb", "rb", "rb+", "wb+", "ab+"
	};
	return modes[static_cast<uint32>(mode)];
}

const wchar_t* gfm::utils::file::ModeTypeToWString(FileOpenMode mode) noexcept {
	static constexpr const wchar_t* const modes[] = {
		L"w", L"r", L"r+", L"w+", L"a+", L"wb", L"rb", L"rb+", L"wb+", L"ab+"
	};
	return modes[static_cast<uint32>(mode)];
}