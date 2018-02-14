#pragma once
#ifndef PIPELINE_TYPE_H
#define PIPELINE_TYPE_H
namespace gfm {
namespace INTERNAL {
namespace gpu {

	enum class PipelineType {
		eRECTANGLE2D,
		eCIRCLE2D,
		eMAX_NUM,
		eSTART_NUM = eRECTANGLE2D,
		eNONE = -1
	};

}//gpu
}//INTERNAL
}//gfm
#endif //PIPELINE_TYPE_H