#pragma once
#ifndef FILE_OPEN_MODE_H
#define FILE_OPEN_MODE_H
namespace gfm {
namespace utils {
namespace file {

enum class FileOpenMode
{
	eTEXT_WRITE,
	eTEXT_READ,
	eTEXT_READ_UPDATE,
	eTEXT_WRITE_UPDAE,
	eTEXT_APPEND_UPDATE,
	eBINARY_WRITE,
	eBINARY_READ,
	eBINARY_READ_UPDATE,
	eBINARY_WRITE_UPDAE,
	eBINARY_APPEND_UPDATE,
};


const char* ModeTypeToString(FileOpenMode mode) noexcept;
const wchar_t* ModeTypeToWString(FileOpenMode mode) noexcept;
}//file
}//utils
}//gfm
#endif // FILE_OPEN_MODE_H