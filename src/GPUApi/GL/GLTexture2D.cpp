#include "GLTexture2D.h"
#include "../thirdparty/stb/stbimage.h"
#include "../../Utils/File/FileExists.h"

//TODO DEFINETLY DO CACHE THESE FILES 

gfm::INTERNAL::gpu::GL::GLTexture2D::GLTexture2D(const String& filePath)
	: m_filePath(filePath)
	, m_borderColor(0.0f, 0.0f, 0.0f, 0.0f)
	, m_minFilter(TextureFilter::eLINEAR)
	, m_maxFiler(TextureFilter::eLINEAR)
	, m_xTextureWrap(TextureWrap::eCLAMP)
	, m_yTextureWrap(TextureWrap::eCLAMP)
	, m_format(TextureFormat::eRGBA)
	, m_flipVertical(false)
	, m_flipHorizontal(false) {
	LoadFromPath();
}

gfm::INTERNAL::gpu::GL::GLTexture2D::GLTexture2D(const String& filePath, const TextureOptions& options)
	: m_filePath(filePath)
	, m_borderColor(options.borderColor)
	, m_minFilter(options.minFilter)
	, m_maxFiler(options.maxFiler)
	, m_xTextureWrap(options.xTextureWrap)
	, m_yTextureWrap(options.yTextureWrap)
	, m_format(options.textureFormat)
	, m_flipVertical(options.flipVertical)
	, m_flipHorizontal(options.flipHorizontal) {
	LoadFromPath();
}

gfm::INTERNAL::gpu::GL::GLTexture2D::GLTexture2D(uint32 width, uint32 height, TextureFormat format)
	: GLTexture2D(String::empty) {
	m_width = width;
	m_height = height;
	m_format = format;
}

gfm::INTERNAL::gpu::GL::GLTexture2D::GLTexture2D(uint32 width, uint32 height, const TextureOptions& options)
	: GLTexture2D(String::empty, options) {
	m_width = width;
	m_height = height;
}

void gfm::INTERNAL::gpu::GL::GLTexture2D::LoadFromPath() {
	Bind();
	if(m_filePath != String::empty) {
		bool fileExists = utils::file::FileExists(m_filePath);
		if(!fileExists) {
			GFM_DEBUG_ASSERT(false, GFM_STRING("The file: {0} does not exists or can not be opened!"), m_filePath);
			throw std::invalid_argument("texture File doesnt Exist!");
		}
		char* filename = reinterpret_cast<char*>(alloca(m_filePath.Length() + 1));
		detail::CStringHelper::Convert(m_filePath.CStr(), filename, m_filePath.Length() + 1);
		utils::int32 texchannels;
		utils::int32 stbFormat = (m_format == TextureFormat::eRGBA) ? STBI_rgb_alpha : STBI_rgb;
		stbi_uc* pixels = stbi_load(filename, &m_width, &m_height, &texchannels, stbFormat);
		stbi_image_free(pixels);
	}
}

void gfm::INTERNAL::gpu::GL::GLTexture2D::UploadData(const void* pixels) {

}

void gfm::INTERNAL::gpu::GL::GLTexture2D::UploadData(const Vec4& color) {

}

void gfm::INTERNAL::gpu::GL::GLTexture2D::UploadData(utils::uint32 color) {

}

const gfm::String& gfm::INTERNAL::gpu::GL::GLTexture2D::GetFilePath() const noexcept {
	return m_filePath;
}

gfm::INTERNAL::gpu::GL::GLTexture2D::int32 gfm::INTERNAL::gpu::GL::GLTexture2D::GetFormatStride() const noexcept {
	return GLTexture::TextureFormatToStride(m_format);
}

gfm::INTERNAL::gpu::GL::GLTexture2D::TextureFormat gfm::INTERNAL::gpu::GL::GLTexture2D::GetTextureFormat() const noexcept {
	return m_format;
}

gfm::utils::int32 gfm::INTERNAL::gpu::GL::GLTexture2D::GetWidth() const noexcept {
	return m_width;
}

gfm::utils::int32 gfm::INTERNAL::gpu::GL::GLTexture2D::GetHeight() const noexcept {
	return m_height;
}


