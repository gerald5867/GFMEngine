#pragma once
#ifndef GL_WINDOW_H
#define GL_WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../Utils/Types.h"
#include "../Window.h"
#include "../Keyboard.h"
#include "../MouseButtons.h"
//#include "../../Macro/NoInline.h"

namespace gfm {
namespace INTERNAL {
namespace gpu {
	class Context;
namespace GL {
	class GLContext;
}
}//gpu
}//INTERNAL
namespace input {
class GLWindow final : public Window
{
	private:
		friend class gfm::INTERNAL::gpu::Context;
		friend class gfm::INTERNAL::gpu::GL::GLContext;

	public:
		GFM_APICALL virtual ~GLWindow() noexcept;
		GLWindow(utils::uint32 width, utils::uint32 height, const String& titleName, bool show = true, bool resizable = false);

		GFM_APICALL virtual void SetKeyCallback(KeyCallBackPtr callback) noexcept override;
		GFM_APICALL virtual void SetMouseCallback(MouseCallBackPtr callback) noexcept override;
		GFM_APICALL virtual void SetResizeCallback(ResizeCallbackPtr callback) noexcept override;
		GFM_APICALL virtual void SetCursorPosCallback(CursorPosCallBackPtr callback) noexcept override;
		GFM_APICALL virtual void SetScrollCallback(ScrollCallBackPtr callback) noexcept override;

		GFM_APICALL virtual void Show() override;
		GFM_APICALL virtual void Hide() override;
		GFM_APICALL virtual void EnableResize() const override;
		GFM_APICALL virtual bool IsOpen() const override;

		GFM_APICALL virtual void Initialize() override;
		GFM_APICALL virtual void SwapBuffers() const override;
		GFM_APICALL virtual void SetSwapInterval(utils::uint32 interval) const override;
		GFM_APICALL virtual void SetViewport(utils::uint32 x, utils::uint32 y, utils::uint32 width, utils::uint32 height) const override;

		GFM_APICALL virtual void Clear() const override;
		GFM_APICALL virtual void Update() override;
		GFM_APICALL /*GFM_NO_INLINE*/ virtual void SetTitle(const String& title) override;

	private:
		static void InternWindowResizedCallback(GLFWwindow* window, int width, int height) noexcept;
		static void InternKeyboardCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
		static void InternMouseCallback(GLFWwindow * window, int button, int action, int mods);
		static void InternCursorPosCallBack(GLFWwindow * window, double xpos, double ypos);
		static void InternScrollCallback(GLFWwindow * window, double xoffset, double yoffset);

		static GLWindow * GLWindow::GetWindowPtr(GLFWwindow * wnd);

	protected:
		GLFWwindow *	  m_window = nullptr;

	private:

		ResizeCallbackPtr    m_resizeCallback = nullptr;
		KeyCallBackPtr       m_keyCallback = nullptr;
		MouseCallBackPtr     m_mouseCallback = nullptr;
		CursorPosCallBackPtr m_cursorPosCallback = nullptr;
		ScrollCallBackPtr    m_scrollCallback = nullptr;
};
}//namespace input
}//namespace gfm
#endif // GL_WINDOW_H