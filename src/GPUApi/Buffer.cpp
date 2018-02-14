#include "Buffer.h"

gfm::INTERNAL::gpu::Buffer::Buffer(BufferUsage usage, BufferType type) :
	m_usage(usage), m_type(type)
{}

gfm::INTERNAL::gpu::BufferUsage gfm::INTERNAL::gpu::Buffer::GetUsage() const noexcept {
	return m_usage;
}

gfm::INTERNAL::gpu::BufferType gfm::INTERNAL::gpu::Buffer::GetType() const noexcept {
	return m_type;
}
