#pragma once
#ifndef SHADER_TYPE_H
#define SHADER_TYPE_H
#include "../Utils/Types.h"

namespace gfm {
namespace INTERNAL {
namespace gpu {

	enum class ShaderType {
		eVERTEX = 0x8B31,
		eFRAGMENT = 0x8B30,
		eGEOMETRY = 0x8DD9,
		eTESSELATION_EVALUATION = 0x8E87,
		eTESSELATION_CONTROL = 0x8E88,
		eSHADER_NONE = -1
	};

}//INTERNAL
}//graphic
}//gfm
#endif // SHADER_TYPE_H