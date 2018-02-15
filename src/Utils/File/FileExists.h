#pragma once
#ifndef FILE_EXISTS_H
#define FILE_EXISTS_H
#include "FileOpenMode.h"
#include "CFileHelper.h"
#include "../../DataStructures/String.h"

namespace gfm {
namespace utils {
namespace file {

bool FileExists(const String& filePath);

}//file
}//utils
}//gfm
#endif // FILE_EXISTS_H