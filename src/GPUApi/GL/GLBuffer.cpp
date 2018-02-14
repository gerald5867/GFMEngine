#pragma once
#include "../../Macro/Assertions.h"
#include "GLBuffer.h"

template<typename DerivedType>
volatile std::atomic<gfm::utils::uint32> gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>::ms_currentBoundBuffer;

template<typename DerivedType>
gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>& gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>::operator=(GLBuffer<DerivedType>&& other) {
	if (this != &other) {
		m_id = other.m_id;
		m_type = other.m_type;
		m_usage = other.m_usage;
		other.m_id = 0;
	}
	return *this;
}

template<typename DerivedType>
gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>::~GLBuffer() noexcept {
	Destroy();
}

template<typename DerivedType>
gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>::GLBuffer(BufferUsage usage, BufferType type) :
Buffer(usage, type)
{
	Create();
}

template<typename DerivedType>
gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>::GLBuffer(GLBuffer<DerivedType>&& other) :
m_id(other.m_id), Buffer(other.m_usage, other.m_type) {
	other.m_id = 0;
}

template<typename DerivedType>
void gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>::Bind() const noexcept {
	if (ms_currentBoundBuffer == m_id) {
		return;
	}
	ASSERT_GL(glBindBuffer(static_cast<utils::uint32>(m_type), static_cast<utils::uint32>(m_id)));
	ms_currentBoundBuffer = m_id;
}

template<typename DerivedType>
void gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>::Unbind() const noexcept {
	if (ms_currentBoundBuffer == 0) {
		return;
	}
	ASSERT_GL(glBindBuffer(static_cast<utils::uint32>(m_type), 0));
	ms_currentBoundBuffer = 0;
}

template<typename DerivedType>
void gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>::Create() const noexcept {
	GFM_DEBUG_ASSERT(m_id == 0, GFM_STRING("Buffer is already Created! ID: {0}"), m_id);
	ASSERT_GL(glGenBuffers(1, &m_id));
	Bind();
}

template<typename DerivedType>
void gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>::Destroy() const noexcept {
	if(m_id == 0) {
		return;
	}
	ASSERT_GL(glDeleteBuffers(1, &m_id));
	m_id = 0;
}

template<typename DerivedType>
bool gfm::INTERNAL::gpu::GL::GLBuffer<DerivedType>::IsBound() const noexcept {
	return ms_currentBoundBuffer == m_id;
}

template class gfm::INTERNAL::gpu::GL::GLBuffer<gfm::INTERNAL::gpu::GL::GLVertexBuffer>;
template class gfm::INTERNAL::gpu::GL::GLBuffer<gfm::INTERNAL::gpu::GL::GLIndexBuffer>;
template class gfm::INTERNAL::gpu::GL::GLBuffer<gfm::INTERNAL::gpu::GL::GLUniformBuffer>;
