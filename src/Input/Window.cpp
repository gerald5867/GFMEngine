#include "Window.h"
#include "../Memory/UniquePointer.h"
#include "../GPUApi/Context.h"
#include "../Memory/DefaultAllocator.h"
#include "GL/GLWindow.h"

const gfm::String& gfm::input::Window::GetName() const noexcept {
	return m_titleName;
}


gfm::input::Window::Window(utils::uint32 width, utils::uint32 height, const String& titleName) :
m_width(width), m_height(height), m_titleName(titleName){
}


gfm::memory::UniquePointer<gfm::input::Window> gfm::input::Window::Create(
	utils::uint32 width, utils::uint32 height, const String & name, bool isShow, bool resizable) {
	using namespace INTERNAL::gpu;
	switch(FindBestGraphicAPI()) {
		case GraphicAPI::eOPENGL:
			return memory::UniquePointer<Window>(dynamic_cast<Window*>(memory::DefaultAllocator::AllocateObject<GLWindow>(width, height, name, isShow, resizable)));
	}
	GFM_DEBUG_BREAK;
}

gfm::utils::uint32 gfm::input::Window::GetWidth() const noexcept {
	return m_width;
}

gfm::utils::uint32 gfm::input::Window::GetHeight() const noexcept {
	return m_height;
}