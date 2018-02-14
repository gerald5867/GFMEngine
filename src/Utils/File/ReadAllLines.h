#pragma once
#ifndef READ_ALL_LINES_H
#define READ_ALL_LINES_H
#include "FileOpenMode.h"
#include "CFileHelper.h"
#include "../../DataStructures/String.h"

namespace gfm {
namespace utils {
namespace file {

	String ReadAllLines(const String& filePath);
	void ReadAllLines(String& buffer, const String& filePath);

}//file
}//utils
}//gfm
#endif // READ_ALL_LINES_H