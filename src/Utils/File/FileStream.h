#pragma once
#ifndef FILE_STREAM_H
#define FILE_STREAM_H
#include <stdio.h>
#include "FileOpenMode.h"
#include "../Types.h"

namespace gfm {
namespace utils {
namespace file {

class FileStream final
{
	public:
		FileStream(const char* filePath, FileOpenMode openMode);
		FileStream(const wchar_t* filePath, FileOpenMode openMode);
		FileStream() = default;

		~FileStream() noexcept;

	public:
		void Open(const char* filePath, FileOpenMode mode);
		void Open(const wchar_t* filePath, FileOpenMode mode);
		utils::uint64 GetSize() const noexcept;
		bool IsOpen() const noexcept;

		void Close() const noexcept;
		uint32 Write(void* buffer, uint32 elemntSize, uint32 bufferSize) const;
		uint32 Write(const char* buffer, uint32 elementCount) const;
		uint32 Read(void* buffer, uint32 elementSize, uint32 elementCount) const;
		uint32 Read(char* buffer, uint32 elementCount);

	private:
		FILE* m_fileHandle = nullptr;
		utils::uint64 m_size = 0;
};
}//file
}//utils
}//gfm
#endif // FILE_STREAM_H