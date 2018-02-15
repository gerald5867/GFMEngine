#include "GLTexture.h"

template<typename DerivedType, utils::uint32 TextureType>
volatile std::atomic<gfm::utils::uint32> gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::s_boundTextureID = 0;

template<typename DerivedType, utils::uint32 TextureType>
volatile std::atomic<gfm::utils::uint32> gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::s_boundTextureSlot = 0;

template<typename DerivedType, utils::uint32 TextureType>
void gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::Unbind(utils::int32 slot /*= 0*/) {
	if (s_boundTextureID != 0) {
		s_boundTextureID = 0;
		glBindTexture(TextureType, 0);
	}
	BindSlot(slot);
}


template<typename DerivedType, utils::uint32 TextureType>
void gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::Bind(utils::int32 slot /*= 0*/) {
	if (s_boundTextureID != m_id) {
		s_boundTextureID = m_id;
		glBindTexture(TextureType, m_id);
	}
	BindSlot(slot);
}

template<typename DerivedType, utils::uint32 TextureType>
void gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::BindSlot(utils::int32 slot) {
	GFM_DEBUG_ASSERT(slot > 0 && slot <= 32, "Texture slot must be between 32 and 0 slot was : {0}", slot);
	if (s_boundTextureSlot != slot) {
		s_boundTextureSlot = slot;
		glActiveTexture(GL_TEXTURE0 + slot);
	}
}

template<typename DerivedType, utils::uint32 TextureType>
gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::GLTexture() {
	glGenTextures(1, &m_id);
}

template<typename DerivedType, utils::uint32 TextureType>
gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::~GLTexture() {
	glDeleteTextures(1, &m_id);
	m_id = 0;
}

template<typename DerivedType, utils::uint32 TextureType>
gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::TextureWrapToGL(TextureWrap wrap) {
	switch (wrap) {
		case TextureWrap::eCLAMP:			return GL_CLAMP;
		case TextureWrap::eCLAMP_TO_BORDER:	return GL_CLAMP_TO_BORDER;
		case TextureWrap::eCLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
		case TextureWrap::eREPEAT:			return GL_REPEAT;
		case TextureWrap::eMIRRORED_REPEAT:	return GL_MIRRORED_REPEAT;
	}
	GFM_DEBUG_BREAK;
	return TextureWrap::NONE; // warning fix;
}

template<typename DerivedType, utils::uint32 TextureType>
gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::TextureFormatToGL(TextureFormat format) {
	switch (format) {
		case TextureFormat::eRGB:return GL_RGB;
		case TextureFormat::eRGBA:return GL_RGBA;
	}
	GFM_DEBUG_BREAK;
	return TextureFormat::NONE; // warning fix;
}

template<typename DerivedType, utils::uint32 TextureType>
gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::TextureFilterToGL(TextureFilter filter) {
	switch (filter) {
		case TextureFilter::LINEAR: return GL_LINEAR;
		case TextureFilter::NEAREST: return GL_NEAREST;
	}
	GFM_DEBUG_BREAK;
	return TextureFilter::NONE; // warning fix;
}

template class gfm::INTERNAL::gpu::GL::GLTexture<GLTexture2D, GL_TEXTURE_2D>;