#pragma once
#include "../DataStructures/String.h"
#include "../Utils/Types.h"
#include "../Macro/ApiCall.h"
#ifndef TEXTURE_H
#define TEXTURE_H
namespace gfm {
namespace graphic {

	GFM_APICALL enum class TextureFormat {
		eR8B8G8A8
	};

	GFM_APICALL class Texture
	{
		public:
			virtual ~Texture() noexcept = default;
			Texture(const String& filePath);
			
			virtual void Bind() = 0;
			virtual void Unbind() = 0;

		public:
			const String& GetFilePath() const noexcept;

		protected:
			utils::uint32 m_width;
			utils::uint32 m_height;
			String m_filePath;
	};

}//graphic
}//gfm
#endif // TEXTURE_H