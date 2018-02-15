#pragma once
#include <atomic>
#include "../../Utils/Types.h"
#include "../../Graphic/Texture.h"
#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H
namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {
	
	class GLTexture2D;

	template<typename DerivedType, utils::uint32 TextureType> // CRTP for s_boundTextureID
	class GLTexture : public virtual graphic::Texture
	{
	public:
		virtual ~GLTexture();
		GLTexture();

		virtual void Bind(utils::int32 slot = 0) override;
		virtual void Unbind(utils::int32 slot = 0) override;

	private:
		static void BindSlot(utils::int32 slot);
		static utils::uint32 TextureFilterToGL(TextureFilter filter);
		static utils::uint32 TextureFormatToGL(TextureFormat format);
		static utils::uint32 TextureWrapToGL(TextureWrap wrap);

	protected:
		utils::uint32 m_id = 0;
		utils::int32 m_boundSlot = 0;

	private:
		volatile static std::atomic<utils::uint32> s_boundTextureID;
		volatile static std::atomic<utils::uint32> s_boundTextureSlot;
	};

}//GL
}//gpu
}//INTERNAL
}//gfm
#endif // GL_TEXTURE_H