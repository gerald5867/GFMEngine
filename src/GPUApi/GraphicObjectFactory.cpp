#include "GraphicObjectFactory.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "UniformBuffer.h"
#include "GL/GLPipelineLayout.h"
#include "GL/GLIndexBuffer.h"
#include "GL/GLUniformBuffer.h"
#include "GL/GLVertexBuffer.h"
#include "../Memory/DefaultAllocator.h"

gfm::INTERNAL::gpu::GraphicObjectFactory* gfm::policy::MakeSingletonPtr<gfm::INTERNAL::gpu::GraphicObjectFactory>::mp_instance = nullptr;

gfm::INTERNAL::gpu::GraphicObjectFactory& gfm::INTERNAL::gpu::GraphicObjectFactory::Initialize(GraphicAPI usedAPI) {
	if (mp_instance == nullptr) {
		mp_instance = reinterpret_cast<GraphicObjectFactory*>(memory::DefaultAllocator::Allocate(sizeof(GraphicObjectFactory)));
		new (mp_instance) GraphicObjectFactory();
		mp_instance->m_API = usedAPI; 
	}
	return *mp_instance;
}

void gfm::INTERNAL::gpu::GraphicObjectFactory::Destroy() noexcept {
	if (mp_instance != nullptr) {
		memory::DefaultAllocator::Deallocate(mp_instance);
		mp_instance = nullptr;
	}
	GFM_DEBUG_BREAK;
}

gfm::memory::UniquePointer<gfm::INTERNAL::gpu::VertexBuffer> gfm::INTERNAL::gpu::GraphicObjectFactory::CreateVertexBuffer(BufferUsage usage) const {
	switch(m_API) {
	case GraphicAPI::eOPENGL:
		GFM_DEBUG_ASSERT(GL::GLPipelineLayout::GetCurrentBoundLayoutID() != 0, GFM_STRING("When you create a VertexBuffer you must bind an PipelineLayout!"));
		return memory::UniquePointer<VertexBuffer>(m_allocator.AllocateObject<GL::GLVertexBuffer>(usage));
	}
	GFM_DEBUG_BREAK;
}

gfm::memory::UniquePointer<gfm::INTERNAL::gpu::IndexBuffer> gfm::INTERNAL::gpu::GraphicObjectFactory::CreateIndexBuffer(BufferUsage usage) const {
	switch(m_API) {
	case GraphicAPI::eOPENGL:
		return memory::UniquePointer<IndexBuffer>(m_allocator.AllocateObject<GL::GLIndexBuffer>(usage));
	}
	GFM_DEBUG_BREAK;
}

gfm::memory::UniquePointer<gfm::INTERNAL::gpu::UniformBuffer> gfm::INTERNAL::gpu::GraphicObjectFactory::CreateUniformBuffer(BufferUsage usage) const
{
	switch (m_API) {
	case GraphicAPI::eOPENGL:
		return memory::UniquePointer<UniformBuffer>(m_allocator.AllocateObject<GL::GLUniformBuffer>(usage));
	}
	GFM_DEBUG_BREAK;
}

gfm::memory::UniquePointer<gfm::INTERNAL::gpu::PipelineLayout> gfm::INTERNAL::gpu::GraphicObjectFactory::CreatePipelineLayout() const {
	switch(m_API) {
	case GraphicAPI::eOPENGL:
		return memory::UniquePointer<PipelineLayout>(m_allocator.AllocateObject<GL::GLPipelineLayout>());
	}
	GFM_DEBUG_BREAK;
}
