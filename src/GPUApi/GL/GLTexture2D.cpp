#include "GLTexture2D.h"

gfm::INTERNAL::gpu::GL::GLTexture2D::GLTexture2D(const String& filePath) {

}

gfm::INTERNAL::gpu::GL::GLTexture2D::GLTexture2D(const String& filePath, const TextureOptions& options) {

}

gfm::INTERNAL::gpu::GL::GLTexture2D::GLTexture2D(uint32 width, uint32 height, TextureFormat format) {

}

gfm::INTERNAL::gpu::GL::GLTexture2D::GLTexture2D(uint32 width, uint32 height, TextureFormat format, const TextureOptions& options) {

}

const gfm::String& gfm::INTERNAL::gpu::GL::GLTexture2D::GetFilePath() const noexcept {

}

gfm::INTERNAL::gpu::GL::GLTexture2D::int32 gfm::INTERNAL::gpu::GL::GLTexture2D::GetFormatStride() const noexcept {

}

gfm::INTERNAL::gpu::GL::GLTexture2D::TextureFormat gfm::INTERNAL::gpu::GL::GLTexture2D::GetTextureFormat() const noexcept {
	return m_format;
}

gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLTexture2D::GetWidth() const noexcept {
	return m_width;
}

gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLTexture2D::GetHeight() const noexcept {
	return m_height;
}

void gfm::INTERNAL::gpu::GL::GLTexture2D::UploadData(const void* pixels) {

}

void gfm::INTERNAL::gpu::GL::GLTexture2D::UploadData(const Vec4& color) {

}

void gfm::INTERNAL::gpu::GL::GLTexture2D::UploadData(utils::uint32 color) {

}
