#include "ErrorHandler.h"
#include "..\Memory\DefaultAllocator.h"
#include "GL\GLErrorHandler.h"

thread_local gfm::INTERNAL::gpu::ErrorHandler* gfm::INTERNAL::gpu::ErrorHandler::mp_instance = nullptr;

gfm::INTERNAL::gpu::ErrorHandler& gfm::INTERNAL::gpu::ErrorHandler::Initialize(GraphicAPI api) {
	if(mp_instance != nullptr) {
		return *mp_instance;
	}
	switch(api) {
	case GraphicAPI::eOPENGL:
		mp_instance = memory::DefaultAllocator::AllocateObject<GL::GLErrorHandler>();
	}
	return *mp_instance;
}

void gfm::INTERNAL::gpu::ErrorHandler::Destroy() noexcept {
	if(mp_instance != nullptr) {
		memory::DefaultAllocator::DeallocateObject(mp_instance);
		mp_instance = nullptr;
	}
}

gfm::INTERNAL::gpu::ErrorHandler& gfm::INTERNAL::gpu::ErrorHandler::Instance() {
	return *mp_instance;
}

