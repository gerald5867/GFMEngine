#pragma once
#include <stdio.h>
#include "ReadAllLines.h"
#include "../Logger.h"
gfm::String gfm::utils::file::ReadAllLines(const String & filePath) {
	String buffer;
	ReadAllLines(buffer, filePath);
	return buffer;
}

void gfm::utils::file::ReadAllLines(String & buffer, const String & filePath) {
	FILE* file = CFileHelper::OpenFile(filePath.CStr(), ModeTypeToWString(FileOpenMode::eBINARY_READ));
	if(file == nullptr) {
		GFM_LOGGER_ERROR("Could not Open File : {0}", filePath);
		return;
	}
	::fseek(file, 0, SEEK_END);
	auto size = ::ftell(file);
	buffer.Resize(size + 1);
	::fseek(file, 0, SEEK_SET);
	::fread(buffer.CStr(), sizeof(String::CharType), size / sizeof(String::CharType), file);
	::fclose(file);
}
