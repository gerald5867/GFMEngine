#include "GL.h"
#include "GLTexture.h"

template<typename DerivedType, gfm::utils::uint32 TextureType>
volatile std::atomic<gfm::utils::uint32> gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::s_boundTextureID = 0;

template<typename DerivedType, gfm::utils::uint32 TextureType>
volatile std::atomic<gfm::utils::uint32> gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::s_boundTextureSlot = 0;

template<typename DerivedType, gfm::utils::uint32 TextureType>
void gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::Unbind(utils::int32 slot /*= 0*/) {
	if (s_boundTextureID != 0) {
		s_boundTextureID = 0;
		ASSERT_GL(glBindTexture(TextureType, 0));
	}
	BindSlot(slot);
}


template<typename DerivedType, gfm::utils::uint32 TextureType>
void gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::Bind(utils::int32 slot /*= 0*/) {
	if (s_boundTextureID != m_id) {
		s_boundTextureID = m_id;
		ASSERT_GL(glBindTexture(TextureType, m_id));
	}
	BindSlot(slot);
}

template<typename DerivedType, gfm::utils::uint32 TextureType>
void gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::BindSlot(utils::int32 slot) {
	GFM_DEBUG_ASSERT(slot >= 0 && slot <= 32, GFM_STRING("Texture slot must be between 32 and 0 slot was : {0}"), slot);
	if (s_boundTextureSlot != slot) {
		s_boundTextureSlot = slot;
		ASSERT_GL(glActiveTexture(GL_TEXTURE0 + slot));
	}
}

template<typename DerivedType, gfm::utils::uint32 TextureType>
gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::GLTexture() {
	glGenTextures(1, &m_id);
}

template<typename DerivedType, gfm::utils::uint32 TextureType>
gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::~GLTexture() {
	glDeleteTextures(1, &m_id);
	m_id = 0;
}

template<typename DerivedType, gfm::utils::uint32 TextureType>
gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::TextureWrapToGL(TextureWrap wrap) {
	switch (wrap) {
		case TextureWrap::eCLAMP:			return GL_CLAMP;
		case TextureWrap::eCLAMP_TO_BORDER:	return GL_CLAMP_TO_BORDER;
		case TextureWrap::eCLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
		case TextureWrap::eREPEAT:			return GL_REPEAT;
		case TextureWrap::eMIRRORED_REPEAT:	return GL_MIRRORED_REPEAT;
	}
	GFM_DEBUG_BREAK;
	static_cast<utils::uint32>(TextureWrap::eNONE); // warning fix;
}

template<typename DerivedType, gfm::utils::uint32 TextureType>
gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::TextureFormatToStride(TextureFormat format) {
	enum FormatStrides {
		ChannelCount1 = 1,
		ChannelCount2 = 2,
		ChannelCount3 = 3,
		ChannelCount4 = 4
	};
	switch(format) {
		case TextureFormat::eRGB: return ChannelCount3;
		case TextureFormat::eRGBA: return ChannelCount4;
	}
	GFM_DEBUG_BREAK;
	return std::numeric_limits<utils::uint32>::max(); // warning fix
}

template<typename DerivedType, gfm::utils::uint32 TextureType>
gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::TextureFormatToGL(TextureFormat format) {
	switch (format) {
		case TextureFormat::eRGB:return GL_RGB;
		case TextureFormat::eRGBA:return GL_RGBA;
	}
	GFM_DEBUG_BREAK;
	return static_cast<utils::uint32>(TextureFormat::eNONE); // warning fix;
}

template<typename DerivedType, gfm::utils::uint32 TextureType>
gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLTexture<DerivedType, TextureType>::TextureFilterToGL(TextureFilter filter) {
	switch (filter) {
		case TextureFilter::eLINEAR: return GL_LINEAR;
		case TextureFilter::eNEAREST: return GL_NEAREST;
	}
	GFM_DEBUG_BREAK;
	return static_cast<utils::uint32>(TextureFilter::eNONE); // warning fix;
}

template class gfm::INTERNAL::gpu::GL::GLTexture<gfm::INTERNAL::gpu::GL::GLTexture2D, GL_TEXTURE_2D>;