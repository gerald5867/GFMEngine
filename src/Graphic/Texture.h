#pragma once
#include "../DataStructures/String.h"
#include "../Math/Vector.h"
#include "../Utils/Types.h"
#include "../Macro/ApiCall.h"
#ifndef TEXTURE_H
#define TEXTURE_H
namespace gfm {
namespace graphic {

	GFM_APICALL enum class TextureFormat {
		eRGBA, eRGB, eNONE = -1
	};

	GFM_APICALL enum class TextureWrap
	{
		eREPEAT, eCLAMP, eMIRRORED_REPEAT, eCLAMP_TO_EDGE, eCLAMP_TO_BORDER, eNONE = -1
	};

	GFM_APICALL enum class TextureFilter
	{
		eLINEAR, eNEAREST, eNONE = -1,
	};

	GFM_APICALL struct TextureOptions final {
		math::Vec4 borderColor;
		TextureFilter minFilter;
		TextureFilter maxFiler;
		TextureWrap xTextureWrap;
		TextureWrap yTextureWrap;
		TextureWrap zTextureWrap;
		TextureFormat textureFormat;
		bool flipVertical;
		bool flipHorizontal;
	};

	GFM_APICALL class Texture {
		public:
			virtual ~Texture() noexcept = default;
			
			virtual void Bind(utils::int32 slot = 0) = 0;
			virtual void Unbind(utils::int32 slot = 0) = 0;

			virtual const String& GetFilePath() const noexcept = 0;
			virtual utils::int32 GetFormatStride() const noexcept = 0;
			virtual TextureFormat GetTextureFormat() const noexcept = 0;

		protected:
			Texture() = default;

		public:
			Texture(const Texture&) = delete;
			Texture(Texture&&) = delete;
			Texture& operator = (const Texture&) = delete;
			Texture& operator = (Texture&&) = delete;
	};

}//graphic
}//gfm
#endif // TEXTURE_H