#pragma once
#include "GL\GLGraphicCommandHandler.h"
#include "GraphicCommandHandler.h"
#include "..\Memory\DefaultAllocator.h"

gfm::INTERNAL::gpu::GraphicCommandHandler* gfm::INTERNAL::gpu::GraphicCommandHandler::mp_instance = nullptr;

gfm::INTERNAL::gpu::GraphicCommandHandler& gfm::INTERNAL::gpu::GraphicCommandHandler::Initialize(GraphicAPI api) {
	if(mp_instance != nullptr) {
		return *mp_instance;
	}
	switch(api) {
	case GraphicAPI::eOPENGL:
		mp_instance = memory::DefaultAllocator::AllocateObject<GL::GLGraphicCommandHandler>();
		break;
	}
	return *mp_instance;
}

gfm::INTERNAL::gpu::GraphicCommandHandler& gfm::INTERNAL::gpu::GraphicCommandHandler::Instance() {
	return *mp_instance;
}

void gfm::INTERNAL::gpu::GraphicCommandHandler::Destroy() noexcept {
	if(mp_instance != nullptr) {
		memory::DefaultAllocator::DeallocateObject(mp_instance);
		mp_instance = nullptr;
	}
}
