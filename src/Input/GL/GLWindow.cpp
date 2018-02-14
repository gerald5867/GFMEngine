#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLWindow.h"
#include "../../Macro/Assertions.h"
#include "../../DataStructures/detail/String/CStringHelper.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)

gfm::input::GLWindow::~GLWindow() noexcept {
	glfwDestroyWindow(m_window);
}

void gfm::input::GLWindow::Show() {
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwShowWindow(m_window);
}

void gfm::input::GLWindow::Hide()  {
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwHideWindow(m_window);
}

void gfm::input::GLWindow::EnableResize() const {
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
}

void gfm::input::GLWindow::SwapBuffers() const {
	glfwSwapBuffers(m_window);
}

void gfm::input::GLWindow::SetSwapInterval(utils::uint32 interval) const {
	glfwSwapInterval(interval);
}

void gfm::input::GLWindow::SetViewport(utils::uint32 x, utils::uint32 y, utils::uint32 width, utils::uint32 height) const {
	glViewport(x, y, width, height);
}

void gfm::input::GLWindow::Initialize() {
	using namespace INTERNAL::gpu; // for Context and GraphicAPI
	char* titlename = static_cast<char*>(alloca(m_titleName.Length() + 1));
	detail::CStringHelper::Convert(m_titleName.CStr(), titlename, m_titleName.Length() + 1);
	switch(FindBestGraphicAPI()) {
	case GraphicAPI::eOPENGL:
		m_window = glfwCreateWindow(m_width, m_height, titlename, nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		break;
	}
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, InternKeyboardCallback);
	glfwSetMouseButtonCallback(m_window, InternMouseCallback);
	glfwSetCursorPosCallback(m_window, InternCursorPosCallBack);
	glfwSetWindowSizeCallback(m_window, InternWindowResizedCallback);
	glfwSetScrollCallback(m_window, InternScrollCallback);
}

gfm::input::GLWindow::GLWindow(
	utils::uint32 width, utils::uint32 height, const String& titleName, bool show, bool resizable
) : Window(width, height, titleName) {
	if(!show) {
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	}
	if(!resizable) {
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}
	else {
		EnableResize();
	}
}

gfm::input::GLWindow * gfm::input::GLWindow::GetWindowPtr(GLFWwindow * wnd) {
	return reinterpret_cast<GLWindow*>(glfwGetWindowUserPointer(wnd));
}

void gfm::input::GLWindow::SetKeyCallback(KeyCallBackPtr callback) noexcept {
	m_keyCallback = callback;
}

void gfm::input::GLWindow::SetMouseCallback(MouseCallBackPtr callback) noexcept {
	m_mouseCallback = callback;
}

void gfm::input::GLWindow::SetResizeCallback(ResizeCallbackPtr callback) noexcept {
	m_resizeCallback = callback;
}

void gfm::input::GLWindow::SetCursorPosCallback(CursorPosCallBackPtr callback) noexcept {
	m_cursorPosCallback = callback;
}

void gfm::input::GLWindow::SetScrollCallback(ScrollCallBackPtr callback) noexcept {
	m_scrollCallback = callback;
}

void gfm::input::GLWindow::InternWindowResizedCallback(GLFWwindow* window, int width, int height) noexcept {
	GLWindow* wnd = GetWindowPtr(window);
	wnd->m_width = width;
	wnd->m_height = height;
	GFM_DEBUG_ASSERT(wnd->m_resizeCallback != nullptr, GFM_STRING("was nullptr"));
	wnd->m_resizeCallback(width, height);
}

void gfm::input::GLWindow::InternKeyboardCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	GLWindow * wnd = GetWindowPtr(window);
	GFM_DEBUG_ASSERT(wnd->m_keyCallback != nullptr, GFM_STRING("was nullptr"));
	wnd->m_keyCallback(static_cast<input::KeyboardKey>(key), static_cast<input::KeyboardAction>(action));
}

bool gfm::input::GLWindow::IsOpen() const {
	return !(glfwWindowShouldClose(m_window));
}

void gfm::input::GLWindow::InternMouseCallback(GLFWwindow * window, int button, int action, int mods) {
	GLWindow * wnd = GetWindowPtr(window);
	GFM_DEBUG_ASSERT(wnd->m_mouseCallback != nullptr, GFM_STRING("was nullptr"));
	wnd->m_mouseCallback(static_cast<input::MouseButton>(button), static_cast<input::MouseAction>(action));
}

void gfm::input::GLWindow::InternCursorPosCallBack(GLFWwindow * window, double xpos, double ypos) {
	GLWindow * wnd = GetWindowPtr(window);
	GFM_DEBUG_ASSERT(wnd->m_cursorPosCallback != nullptr, GFM_STRING("was nullptr"));
	wnd->m_cursorPosCallback(static_cast<float>(xpos), static_cast<float>(ypos));
}

void gfm::input::GLWindow::InternScrollCallback(GLFWwindow * window, double xoffset, double yoffset) {
	GLWindow * wnd = GetWindowPtr(window);
	GFM_DEBUG_ASSERT(wnd->m_scrollCallback != nullptr, GFM_STRING("was nullptr"));
	wnd->m_scrollCallback(static_cast<float>(yoffset));
}

void gfm::input::GLWindow::Clear() const {
	glClear(GL_COLOR_BUFFER_BIT);
}

void gfm::input::GLWindow::Update() {
	glfwPollEvents();
}

void gfm::input::GLWindow::SetTitle(const String& title) {
	char* stackConvertBuffer = static_cast<char*>(alloca(title.Length() + 1));
	detail::CStringHelper::Convert(title.CStr(), stackConvertBuffer, title.Length() + 1);
	glfwSetWindowTitle(m_window, stackConvertBuffer);
}


#pragma warning(pop) // 4100 
#endif // _MSC_VER