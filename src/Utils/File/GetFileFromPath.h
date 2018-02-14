#pragma once
#ifndef GET_FILE_FROM_PATH_H
#define GET_FILE_FROM_PATH_H
#include <string>
#include "../Types.h"
#include "../../Macro/BestInline.h"
#include "../../DataStructures/String.h"
namespace gfm {
namespace detail {
struct CStringHelper;
}
}
#include "../../DataStructures/detail/String/CStringHelper.h"

namespace gfm {
namespace utils {
namespace detail {

String GetFileFromPath(const String::CharType* cstr, uint32 size) noexcept;
}//detail
namespace file {

GFM_BEST_INLINE String GetFileFromPath(const String& path) {
	return detail::GetFileFromPath(path.CStr(), path.Length());
}

}//file
}//utils
}//gfm
#endif //GET_FILE_FROM_PATH_H