#include "../../Macro/Assertions.h"
#include "GLIndexBuffer.h"
void gfm::INTERNAL::gpu::GL::GLIndexBuffer::UploadData(const utils::uint16* data, utils::uint32 count) {
	GFM_DEBUG_ASSERT(m_id != 0, GFM_STRING("Buffer was not created!"));
	m_count = count;
	ASSERT_GL(glBindBuffer(static_cast<utils::uint32>(m_type), static_cast<utils::uint32>(m_id)));
	ASSERT_GL(glBufferData(static_cast<utils::uint32>(m_type), count * sizeof(utils::uint16), data, static_cast<utils::uint32>(m_usage)));
}

void gfm::INTERNAL::gpu::GL::GLIndexBuffer::UploadData(const utils::uint32* data, utils::uint32 count) {
	m_count = count;
	GFM_DEBUG_ASSERT(m_id != 0, GFM_STRING("Buffer was not created!"));
	Bind();
	ASSERT_GL(glBufferData(static_cast<utils::uint32>(m_type), count * sizeof(utils::uint32), data, static_cast<utils::uint32>(m_usage)));
}

void gfm::INTERNAL::gpu::GL::GLIndexBuffer::UploadData(const List<utils::uint16>& data) {
	UploadData(data.Raw(), data.Length());
}
void gfm::INTERNAL::gpu::GL::GLIndexBuffer::UploadData(const List<utils::uint32>& data) {
	UploadData(data.Raw(), data.Length());
}

gfm::INTERNAL::gpu::GL::GLIndexBuffer::GLIndexBuffer(BufferUsage usage) :
GLBuffer(usage, BufferType::eINDEX), IndexBuffer(usage),
Buffer(usage, BufferType::eINDEX){

}

gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLIndexBuffer::Count() const noexcept {
	return m_count;
}

