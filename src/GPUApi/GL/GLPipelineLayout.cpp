#include "../../Macro/Assertions.h"
#include "GLPipelineLayout.h"
#include "../GraphicObjectFactory.h"
#include "../PipelineManager.h"
#include "../VertexBufferLayout.h"

gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLPipelineLayout::ms_currentBoundPipelineLayout = 0;

void gfm::INTERNAL::gpu::GL::GLPipelineLayout::CreateFromPipeline(PipelineType type) {
	auto& pipemgr = PipelineManager::instance();
	CreateFromPipeline(pipemgr.GetPipeline(type));
}

void gfm::INTERNAL::gpu::GL::GLPipelineLayout::CreateFromPipeline(const Pipeline& pipeline) {
	GFM_DEBUG_ASSERT(m_buffers.Length() != 0, GFM_STRING("You must Append A Buffer to a PipelineLayout before you can Create It!"));
	m_buffers[m_buffers.Length() - 1]->Bind();
	for(const auto& attr : pipeline.GetVertexAttributes()) {
		ASSERT_GL(glEnableVertexAttribArray(m_attributeCount));
		ASSERT_GL(glVertexAttribPointer(
			m_attributeCount++, 
			attr.componentCount, 
			VertexAttributeTypeToGlTYPE(attr.type), 
			static_cast<utils::uint32>(attr.normalized),
			pipeline.GetVertexAttributesStride(), 
			reinterpret_cast<const void*>(attr.componentOffset)));
	}
}

void gfm::INTERNAL::gpu::GL::GLPipelineLayout::AppendBuffer(const Buffer& buffer) {
	m_buffers.Append(&buffer);
}


gfm::INTERNAL::gpu::GL::GLPipelineLayout::GLPipelineLayout() {
	GFM_DEBUG_ASSERT(m_id == 0, GFM_STRING("VertexArray already Created!"));
	ASSERT_GL(glGenVertexArrays(1, &m_id));
	Bind();
}

gfm::INTERNAL::gpu::GL::GLPipelineLayout::~GLPipelineLayout() noexcept {
	GFM_DEBUG_ASSERT(m_id != 0, GFM_STRING("VertexArray already Destroyed!"));
	ASSERT_GL(glDeleteVertexArrays(1, &m_id));
	if(ms_currentBoundPipelineLayout == m_id) {
		ms_currentBoundPipelineLayout = 0;
	}
}

gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLPipelineLayout::GetCurrentBoundLayoutID() noexcept {
	return ms_currentBoundPipelineLayout;
}

void gfm::INTERNAL::gpu::GL::GLPipelineLayout::Bind() const noexcept {
	if(ms_currentBoundPipelineLayout != m_id) {
		ms_currentBoundPipelineLayout = m_id;
		ASSERT_GL(glBindVertexArray(m_id));
	}
}

void gfm::INTERNAL::gpu::GL::GLPipelineLayout::Unbind() const noexcept {
	if(ms_currentBoundPipelineLayout != 0) {
		ms_currentBoundPipelineLayout = 0;
		ASSERT_GL(glBindVertexArray(0));
	}
}

void gfm::INTERNAL::gpu::GL::GLPipelineLayout::EnableVertexAttribute(const VertexAttribute& attr, utils::uint32 stride) {
	m_buffers[m_buffers.Length() - 1]->Bind();
	ASSERT_GL(glEnableVertexAttribArray(m_attributeCount));
	ASSERT_GL(glVertexAttribPointer(
		m_attributeCount++, 
		attr.componentCount, 
		VertexAttributeTypeToGlTYPE(attr.type), 
		static_cast<utils::uint32>(attr.normalized),
		stride, 
		reinterpret_cast<const void*>(attr.componentOffset)));
}

void gfm::INTERNAL::gpu::GL::GLPipelineLayout::CreateFromVertexBufferLayout(const VertexBufferLayout& layout) {
	for(const auto& attribute : layout.GetAttributes()) {
		ASSERT_GL(glEnableVertexAttribArray(attribute.locationIndex));
		ASSERT_GL(glVertexAttribPointer(
			m_attributeCount++, 
			attribute.componentCount,
			VertexAttributeTypeToGlTYPE(attribute.type),
			static_cast<utils::uint32>(attribute.normalized),
			layout.GetStride(), 
			reinterpret_cast<const void*>(attribute.componentOffset)));
	}
}

