#include "FileExists.h"
#include "../../DataStructures/String.h"
#include "../../Macro/Platform.h"
#include "CFileHelper.h"


bool gfm::utils::file::FileExists(const String& filePath) {
	if(FILE *file = CFileHelper::OpenFile(filePath.CStr(), ModeTypeToWString(FileOpenMode::eBINARY_READ))) {
		::fclose(file);
		return true;
	}
	return false;
}
