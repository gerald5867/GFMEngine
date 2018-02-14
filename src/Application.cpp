#pragma once
#include <GL/glew.h>
#include "Application.h"
#include "Utils/Logger.h"
#include "Memory/MemoryAllocator.h"
#include "GPUApi/GL/GLContext.h"
#include "GPUApi/ErrorHandler.h"
#include "GPUApi/PipelineManager.h"
#include "GPUApi/GraphicCommandHandler.h"
#include "Graphic/IRenderer.h"
gfm::Application* gfm::policy::MakeSingletonPtr<gfm::Application>::mp_instance = nullptr;

void gfm::Application::ResizeCallback(int width, int height) {
	if (width <= 0 || height <= 0) {
		return;
	}
	mp_instance->m_height = height;
	mp_instance->m_width = width;
	mp_instance->m_window->SetViewport(0, 0, width, height);
}

int gfm::Application::GetHeight() const noexcept {
	return m_height;
}

int gfm::Application::GetWidth() const noexcept {
	return m_width;
}

gfm::math::Vec2 gfm::Application::GetSize() const noexcept {
	return gfm::math::Vec2( static_cast<float>(m_width), static_cast<float>(m_height) );
}

void gfm::Application::KeyCallback(input::KeyboardKey key, input::KeyboardAction action) {
	mp_instance->m_keyboard.InternKeyCallback(key, action);
}

const gfm::input::Mouse& gfm::Application::GetMouseModule() const noexcept {
	return m_mouse;
}

const gfm::input::Keyboard& gfm::Application::GetKeyboardModule() const noexcept {
	return m_keyboard;
}


void gfm::Application::MouseCallback(input::MouseButton button, input::MouseAction action) {
	mp_instance->m_mouse.InternKeyCallback(button, action);
}

void gfm::Application::CursorPosCallback(float x, float y) {
	mp_instance->m_mouse.SetPos(x, y);
}

void gfm::Application::ScrollCallback(float position) {
	mp_instance->m_mouse.SetScroll(position);

}

gfm::Application& gfm::Application::Initialize(const char * appName, int startWidth, int startHeight, bool resizeable, bool isShow){
	if (mp_instance != nullptr) {
		return *mp_instance;
	}
	auto bestGPApi = INTERNAL::gpu::FindBestGraphicAPI();
	memory::MemoryAllocator::initialize();
	mp_instance = memory::DefaultAllocator::AllocateObject<Application>(appName, startWidth, startHeight, resizeable, isShow);
	auto& window = *mp_instance->m_window;
	mp_instance->m_height = startHeight;
	mp_instance->m_width = startWidth;
	INTERNAL::gpu::Context::Initialize(bestGPApi, window);
	INTERNAL::gpu::ErrorHandler::Initialize(bestGPApi);
	INTERNAL::gpu::GraphicCommandHandler::Initialize(bestGPApi);
	utils::Logger::instance().Information("Initialize Application was success OpenGL Version : {0}", glGetString(GL_VERSION));
	INTERNAL::gpu::PipelineManager::Initialize(bestGPApi);
	return *mp_instance;
}

bool gfm::Application::KeepAlive() const {
	return m_window->IsOpen();
}

void gfm::Application::Update() {
	graphic::IRenderer::s_renderers.ForEach([](graphic::IRenderer*& pRenderer) {pRenderer->Update();});
	graphic::IRenderer::s_renderers.ForEach([](graphic::IRenderer*& pRenderer) {pRenderer->Render();});
	m_mouse.Update();
	m_keyboard.Update();
	m_mouse.SetIsScrolling(false);
	m_window->SwapBuffers();
	m_window->Update();
}

void gfm::Application::ClearScreen() const noexcept {
	INTERNAL::gpu::GraphicCommandHandler::Instance().Clear(INTERNAL::gpu::ClearTarget::eCOLOR_BUFFER_BIT);
}

void gfm::Application::Destroy() {
	INTERNAL::gpu::PipelineManager::Destroy();
	INTERNAL::gpu::GraphicCommandHandler::Destroy();
	if (mp_instance != nullptr) {
		memory::DefaultAllocator::DeallocateObject(mp_instance);
		mp_instance = nullptr;
	}
	//INTERNAL::gpu::ErrorHandler::Destroy();
	INTERNAL::gpu::Context::Destroy();
}



gfm::Application::Application(const char * appName, int startWidth, int startHeight, bool resizable, bool isShow) :
m_window(input::Window::Create(startWidth, startHeight, appName, isShow, resizable)){
	m_window->SetCursorPosCallback(CursorPosCallback);
	m_window->SetMouseCallback(MouseCallback);
	m_window->SetKeyCallback(KeyCallback);
	m_window->SetScrollCallback(ScrollCallback);
	m_window->SetResizeCallback(ResizeCallback);
	m_window->SetSwapInterval(1);
}