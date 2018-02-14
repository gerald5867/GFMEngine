#include "GLUniformBuffer.h"
#include "..\..\Macro\Assertions.h"

gfm::utils::int32 gfm::INTERNAL::gpu::GL::GLUniformBuffer::s_lastBindingPoint = 1;
gfm::utils::int32 gfm::INTERNAL::gpu::GL::GLUniformBuffer::s_maxBindingCount = 0;
gfm::utils::int32 gfm::INTERNAL::gpu::GL::GLUniformBuffer::s_maxSize = 0;

gfm::INTERNAL::gpu::GL::GLUniformBuffer::GLUniformBuffer(BufferUsage usage)
: GLBuffer(usage, BufferType::eUNIFORM)
, UniformBuffer(usage)
, Buffer(usage, BufferType::eUNIFORM) {
	//TODO: CHECK FOR MAX SIZE
	m_bindingPoint = s_lastBindingPoint++;
}

void gfm::INTERNAL::gpu::GL::GLUniformBuffer::UploadData(const void* data, utils::uint32 size) const {
	Bind();
	ASSERT_GL(glBufferData(static_cast<utils::uint32>(m_type), size, data, static_cast<utils::uint32>(m_usage)));
}

void* gfm::INTERNAL::gpu::GL::GLUniformBuffer::MapMemory(BufferAcces access) const {
	Bind();
	void* data = glMapBuffer(static_cast<utils::uint32>(m_type), static_cast<utils::uint32>(access));
	GFM_DEBUG_ASSERT(data != nullptr, GFM_STRING("Failed to Map Buffer Memory"));
	return data;
}

void gfm::INTERNAL::gpu::GL::GLUniformBuffer::UnmapMemory(void* bufferMemory) const {
	bool success = glUnmapBuffer(static_cast<utils::uint32>(m_type));
	GFM_DEBUG_ASSERT(success, GFM_STRING("Failed to Unmap Buffer Memory"));
}

void gfm::INTERNAL::gpu::GL::GLUniformBuffer::Resize(utils::uint32 newSize) const {
	Bind();
	ASSERT_GL(glBufferData(static_cast<utils::uint32>(m_type), newSize, nullptr, static_cast<utils::uint32>(m_usage)));
}

gfm::utils::int32 gfm::INTERNAL::gpu::GL::GLUniformBuffer::GetBindingPoint() const {
	return m_bindingPoint;
}

gfm::utils::int32 gfm::INTERNAL::gpu::GL::GLUniformBuffer::GetMaximumUboCount() const {
	if(s_maxBindingCount == 0) {
		glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &s_maxBindingCount);
	}
	return s_maxBindingCount;
}

gfm::utils::int32 gfm::INTERNAL::gpu::GL::GLUniformBuffer::GetMaximumSize() const {
	if(s_maxSize == 0) {
		glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &s_maxSize);
	}
	return s_maxSize;
}
