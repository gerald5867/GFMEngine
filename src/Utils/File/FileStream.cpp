#pragma once
#include "FileStream.h"
#include "CFileHelper.h"

gfm::utils::file::FileStream::FileStream(const char* filePath, FileOpenMode openMode) {
	Open(filePath, openMode);
}

gfm::utils::file::FileStream::FileStream(const wchar_t* filePath, FileOpenMode openMode) {
	Open(filePath, openMode);
}

gfm::utils::file::FileStream::~FileStream() noexcept {
	Close();
}

void gfm::utils::file::FileStream::Open(const char* filePath, FileOpenMode mode) {
	m_fileHandle = CFileHelper::OpenFile(filePath, ModeTypeToString(mode));
	if(m_fileHandle == nullptr) {
		return;
	}
	::fseek(m_fileHandle, 0, SEEK_END);
	m_size = ::ftell(m_fileHandle);
	::fseek(m_fileHandle, 0, SEEK_SET);
}

void gfm::utils::file::FileStream::Open(const wchar_t * filePath, FileOpenMode mode) {
	m_fileHandle = CFileHelper::OpenFile(filePath, ModeTypeToWString(mode));
	if(m_fileHandle == nullptr) {
		return;
	}
	::fseek(m_fileHandle, 0, SEEK_END);
	m_size = ::ftell(m_fileHandle);
	::fseek(m_fileHandle, 0, SEEK_SET);
}

gfm::utils::uint64 gfm::utils::file::FileStream::GetSize() const noexcept {
	return m_size;
}

bool gfm::utils::file::FileStream::IsOpen() const noexcept {
	return m_fileHandle != nullptr;
}

void gfm::utils::file::FileStream::Close() const noexcept {
	::fclose(m_fileHandle);
}

gfm::utils::uint32 gfm::utils::file::FileStream::Read(void* buffer, uint32 elementSize, uint32 elementCount) const {
	if(!IsOpen()) {
		return 0;
	}
	return fread(buffer, elementSize, elementCount, m_fileHandle);
}

gfm::utils::uint32 gfm::utils::file::FileStream::Read(char* buffer, uint32 elementCount) {
	if(!IsOpen()) {
		return 0;
	}
	return fread(reinterpret_cast<void*>(buffer), elementCount, elementCount, m_fileHandle);
}

gfm::utils::uint32 gfm::utils::file::FileStream::Write(void * buffer, uint32 elemntSize, uint32 elementCount) const {
	if(!IsOpen()) {
		return 0;
	}
	return fwrite(buffer, elemntSize, elementCount, m_fileHandle);
}

gfm::utils::uint32 gfm::utils::file::FileStream::Write(const char* buffer, uint32 elementCount) const {
	if(!IsOpen()) {
		return 0;
	}
	return fwrite(buffer, elementCount, elementCount, m_fileHandle);
}
