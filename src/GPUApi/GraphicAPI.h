#pragma once
#ifndef GRAPHIC_API_H
#define GRAPHIC_API_H
namespace gfm {
namespace INTERNAL {
namespace gpu {

	enum class GraphicAPI {
		eNONE, eOPENGL, eMAX_NUM
	};

	GraphicAPI FindBestGraphicAPI();
	
}//gpu
}//INTERNAL
}//gfm
#endif // GRAPHIC_API_H