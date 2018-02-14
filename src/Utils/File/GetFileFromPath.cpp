#pragma once
#include "GetFileFromPath.h"

gfm::String gfm::utils::detail::GetFileFromPath(const String::CharType* cstr, uint32 size) noexcept {
	--size;
	while(cstr[size] != '\\' && cstr[size] != '/') {
		if(size == 0) {
			return String("");
		}
		--size;
	}
	return String(&cstr[size + 1]);
}