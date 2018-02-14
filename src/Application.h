#pragma once
#include <iostream>
#include "Policys/Singleton.h"
#include "Input/Window.h"
#include "Memory/UniquePointer.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "GPUAPI/Context.h"
#include "Math/Vector.h"
struct GLFWwindow;
namespace gfm{
namespace INTERNAL {
namespace gpu {
	enum class GraphicAPI;
}
}
namespace memory {
	class DefaultAllocator;
}
	class Application final : public policy::MakeSingletonPtr<Application>
	{
		friend class memory::DefaultAllocator;
	public:
		static gfm::Application& Initialize(const char * appName, int startWidth, int startHeight, bool resizeable, bool isShow);
		static void Destroy();
		void Update();
		void ClearScreen() const noexcept;

		bool KeepAlive() const;

		const input::Mouse& GetMouseModule() const noexcept;
		const input::Keyboard& GetKeyboardModule() const noexcept;

		int GetHeight() const noexcept;
		int GetWidth() const noexcept;
		math::Vec2 GetSize() const noexcept;
	private:
		Application(const char * appName, int startWidth, int startHeight, bool resizable, bool isShow);

		static void ResizeCallback(int width, int height);
		static void KeyCallback(input::KeyboardKey key, input::KeyboardAction action);
		static void MouseCallback(input::MouseButton button, input::MouseAction action);
		static void CursorPosCallback(float x, float y);
		static void ScrollCallback(float position);

	private:
		int			m_width;
		int			m_height;
		const char* m_appName		  = nullptr;

		input::Mouse    m_mouse;
		input::Keyboard m_keyboard;
		memory::UniquePointer<input::Window> m_window;
	};
}

