#pragma once
#include "GL.h"
#include "GLTexture.h"
#include "../../Graphic/Texture2D.h"
#ifndef GL_TEXTURE2D_H
#define GL_TEXTURE2D_H
namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {

	class GLTexture2D final : public GLTexture<GLTexture2D, GL_TEXTURE_2D>, public graphic::Texture2D {
		public:
			using TextureFormat = graphic::TextureFormat;
			using TextureFilter = graphic::TextureFilter;
			using TextureWrap = graphic::TextureWrap;
			using TextureOptions = graphic::TextureOptions;
			using uint32 = utils::uint32;
			using int32 = utils::int32;
			using Vec4 = math::Vec4;

		public:
			GLTexture2D() = default;
			GLTexture2D(const String& filePath);
			GLTexture2D(const String& filePath, const TextureOptions& options);
			GLTexture2D(uint32 width, uint32 height, TextureFormat format);
			GLTexture2D(uint32 width, uint32 height, TextureFormat format, const TextureOptions& options);

			virtual ~GLTexture2D() noexcept = default;

		public:
			virtual const String& GetFilePath() const noexcept override;
			virtual int32 GetFormatStride() const noexcept override;
			virtual TextureFormat GetTextureFormat() const noexcept override;

			virtual uint32 GetWidth() const noexcept override;
			virtual uint32 GetHeight() const noexcept override;

			virtual void UploadData(const void* pixels) override;
			virtual void UploadData(const Vec4& color) override;
			virtual void UploadData(utils::uint32 color) override;

		protected:
			String m_filePath;
			uint32 m_width;
			uint32 m_height;
			Vec4 m_borderColor;
			TextureFilter m_minFilter;
			TextureFilter m_maxFiler;
			TextureWrap m_xTextureWrap;
			TextureWrap m_yTextureWrap;
			TextureFormat m_format;
			bool m_flipVertical;
			bool m_flipHorizontal;
	};
}
}
}
}
#endif  // GL_TEXTURE2D_H