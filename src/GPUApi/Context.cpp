#include "Context.h"
#include "GL/GLContext.h"
#include "../memory/DefaultAllocator.h"

gfm::INTERNAL::gpu::Context* gfm::INTERNAL::gpu::Context::mp_instance = nullptr;

gfm::INTERNAL::gpu::Context & gfm::INTERNAL::gpu::Context::Initialize(GraphicAPI api, input::Window& targetWindow) {
	if(mp_instance != nullptr) {
		return *mp_instance;
	}
	switch(api) {
	case GraphicAPI::eOPENGL:
		mp_instance = memory::DefaultAllocator::AllocateObject<GL::GLContext>(api, targetWindow);
		break;
	}
	mp_instance->m_API = api;
	return *mp_instance;
}

gfm::INTERNAL::gpu::Context & gfm::INTERNAL::gpu::Context::Instance() {
	return *mp_instance;
}

void gfm::INTERNAL::gpu::Context::Destroy() noexcept {
	if(mp_instance != nullptr) {
		memory::DefaultAllocator::DeallocateObject(mp_instance);
		mp_instance = nullptr;
	}
}
