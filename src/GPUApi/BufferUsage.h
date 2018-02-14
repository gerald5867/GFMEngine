#pragma once
#ifndef BUFFER_USAGE_H
#define BUFFER_USAGE_H
#include "../Utils/Types.h"

namespace gfm {
namespace INTERNAL {
namespace gpu  {

	enum class BufferUsage {
		eSTATIC_COPY  = 0x88E6,
		eSTATIC_DRAW  = 0x88E4,
		eSTATIC_READ  = 0x88E5,
		eDYNAMIC_COPY = 0x88EA,
		eDYNAMIC_DRAW = 0x88E8,
		eDYNAMIC_READ = 0x88E9,
		eSTREAM_COPY  = 0x88E2,
		eSTREAM_DRAW  = 0x88E0,
		eSTREAM_READ  = 0x88E1,
	};

}//INTERNAL
}//graphic
}//gfm
#endif //BUFFER_USAGE_H