#pragma once
#ifndef COLOR_H
#define COLOR_H
#include "../Macro/ApiCall.h"
#include "../DataStructures/Array.h"
#include "../Utils/Types.h"
#include "../Math/Vector.h"
#include "../Macro/BestInline.h"
namespace gfm {
namespace graphic {

	struct GFM_APICALL Colorb final
	{
		Colorb(utils::byte R, utils::byte G, utils::byte B, utils::byte A) {
			utils::uint32 rshifter = R;
			utils::uint32 gshifter = G;
			utils::uint32 bshifter = B;
			rgba = rshifter << 24 | gshifter << 16 | bshifter << 8 | A;
		}
		Colorb(utils::uint32 RGBA) {
			rgba = RGBA;
		}
		union {
			utils::uint32 rgba;
			struct {
				utils::byte r;
				utils::byte g;
				utils::byte b;
				utils::byte a;
			};
		};
	
	};

	struct Colorf final
	{
		union {
			gfm::Array<float, 4> rgbaArray;
			gfm::math::Vec4 rgba;
			struct {
				float r;
				float g;
				float b;
				float a;
			};
		};
	
		GFM_BEST_INLINE operator Colorb() {
			typedef typename utils::byte byte;
			return Colorb{
				static_cast<utils::uint32>(
					static_cast<byte>(a) << 24U | static_cast<byte>(b) << 16U |
				static_cast<byte>(g) << 8U | static_cast<byte>(r))
			};
		}
	};


}//graphic
}//gfm
#endif // COLOR_h