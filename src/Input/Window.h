#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include "KeyboardKeys.h"
#include "MouseButtons.h"
#include "../Policys/Noncopyable.h"
#include "../Policys/Nonmoveable.h"
#include "../DataStructures/String.h"
#include "../Macro/ApiCall.h"
#include "../Memory/UniquePointer.h"

struct GLFWwindow;

namespace gfm {
namespace input {

	class Window : public policy::Noncopyable, public policy::Nonmoveable
	{
		public:
			using ResizeCallbackPtr    = void(*) (int, int);
			using KeyCallBackPtr       = void(*) (KeyboardKey, KeyboardAction);
			using MouseCallBackPtr     = void(*) (MouseButton, MouseAction);
			using CursorPosCallBackPtr = void(*) (float, float);
			using ScrollCallBackPtr	   = void(*) (float);

		public:
			GFM_APICALL static memory::UniquePointer<Window> Create(
				utils::uint32 width, utils::uint32 height, const String& name, bool isShow = true, bool resizable = false);

			GFM_APICALL virtual ~Window() noexcept = default;

			GFM_APICALL utils::uint32 GetWidth() const noexcept;
			GFM_APICALL utils::uint32 GetHeight() const noexcept;
			GFM_APICALL const String& GetName() const noexcept;

		public:

			GFM_APICALL virtual void Show() = 0;
			GFM_APICALL virtual void Hide() = 0;
			GFM_APICALL virtual bool IsOpen() const = 0;
			GFM_APICALL virtual void Clear() const = 0;
			GFM_APICALL virtual void Update() = 0;

			GFM_APICALL virtual void SetTitle(const String& title) = 0;
			GFM_APICALL virtual void EnableResize() const = 0;
			GFM_APICALL virtual void SwapBuffers() const = 0;
			GFM_APICALL virtual void SetSwapInterval(utils::uint32 interval) const = 0;
			GFM_APICALL virtual void SetViewport(utils::uint32 x, utils::uint32 y,utils::uint32 width, utils::uint32 height) const = 0;

			GFM_APICALL virtual void SetKeyCallback(KeyCallBackPtr callback) = 0;
			GFM_APICALL virtual void SetMouseCallback(MouseCallBackPtr callback) = 0;
			GFM_APICALL virtual void SetResizeCallback(ResizeCallbackPtr callback) = 0;
			GFM_APICALL virtual void SetCursorPosCallback(CursorPosCallBackPtr callback) = 0;
			GFM_APICALL virtual void SetScrollCallback(ScrollCallBackPtr callback) = 0;

			GFM_APICALL virtual void Initialize() = 0;

		protected:
			Window(utils::uint32 m_width, utils::uint32 m_height, const String& titleName);

		protected:
			utils::uint32 m_width  = 0;
			utils::uint32 m_height = 0;
			String m_titleName;
	};

}//input
}//gfm
#endif// WINDOW_H
