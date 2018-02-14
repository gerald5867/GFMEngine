#include "GLVertexBuffer.h"
#include "../../Macro/Assertions.h"


gfm::INTERNAL::gpu::GL::GLVertexBuffer::GLVertexBuffer(BufferUsage usage) 
: GLBuffer(usage, BufferType::eVERTEX)
, VertexBuffer(usage) 
, Buffer(usage, BufferType::eVERTEX) {
}

void gfm::INTERNAL::gpu::GL::GLVertexBuffer::UploadRawData(const void * data, utils::uint32 size) const {
	GFM_DEBUG_ASSERT(m_id != 0, GFM_STRING("the VertexBuffer must first be created!"));
	Bind();
	ASSERT_GL(glBufferData(static_cast<utils::uint32>(m_type), size, data, static_cast<utils::uint32>(m_usage)));
}

void* gfm::INTERNAL::gpu::GL::GLVertexBuffer::MapMemory(BufferAcces access) const {
	Bind();
	void* data = glMapBuffer(static_cast<utils::uint32>(m_type), static_cast<utils::uint32>(access));
	GFM_DEBUG_ASSERT(data != nullptr, GFM_STRING("Failed to Map Buffer Memory"));
	return data;
}

void gfm::INTERNAL::gpu::GL::GLVertexBuffer::UnmapMemory(void* bufferMemory) const {
	bool success= glUnmapBuffer(static_cast<utils::uint32>(m_type));
	GFM_DEBUG_ASSERT(success, GFM_STRING("Failed to Unmap Buffer Memory"));
}

void gfm::INTERNAL::gpu::GL::GLVertexBuffer::Resize(utils::uint32 newSize) const {
	Bind();
	ASSERT_GL(glBufferData(static_cast<utils::uint32>(m_type), newSize, nullptr, static_cast<utils::uint32>(m_usage)));
}
