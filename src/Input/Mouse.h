#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Math/Vector.h"
#include "MouseButtons.h"

namespace gfm
{
	class Application;
namespace input
{

	class Mouse
	{
	public:
		using CallbackFuncPtr = void(*)(MouseButton, MouseAction);
		friend class Application;
	protected:
		static const constexpr size_t ms_BUTTONARRAYSIZE = (static_cast<size_t>(MouseButton::eBUTTON_LAST) + 1);
		bool m_pressedButtonsThisFrame[ms_BUTTONARRAYSIZE];
		bool m_pressedButtonsNextFrame[ms_BUTTONARRAYSIZE];
		bool m_pressedButtonsLastFrame[ms_BUTTONARRAYSIZE];
		
		float m_xLastFrame;
		float m_xThisFrame;
		float m_yLastFrame;
		float m_yThisFrame;

		float m_scrollLastFrame;
		float m_scrollThisFrame;
		float m_scrollNextFrame;

		bool  m_isScrolling;
		CallbackFuncPtr m_otherCallback = nullptr;

	public:
		Mouse();
		virtual ~Mouse() noexcept = default;

		Mouse(Mouse && other)					 = delete;
		Mouse & operator = (Mouse && other)		 = delete;
		Mouse(const Mouse & other)				 = delete;
		Mouse & operator = (const Mouse & other) = delete;

		float GetX()  const noexcept;
		float GetY()  const noexcept;
		math::Vec2 GetPosition()  const noexcept;

		float GetLastFrameX()  const noexcept;
		float GetLastFrameY()  const noexcept;
		math::Vec2 GetLastFramePosition()  const noexcept;
		
		float GetDeltaX() const noexcept; 
		float GetDeltaY() const noexcept;
		math::Vec2 GetDeltaPosition() const noexcept;

		void SetCallback(CallbackFuncPtr func);

		bool IsPressed(MouseButton btn)  const;
		bool WasUpLastFrame(MouseButton btn) const;
		bool WasDownLastFrame(MouseButton btn) const;
		bool IsUp(MouseButton btn)const;
		bool IsDown(MouseButton btn) const;
		bool IsScrollingIn() const;
		bool IsScrollingOut()const;

		static bool IsValidButton(MouseButton btn) noexcept;
	
	private:
		bool CheckButtonValidation(MouseButton btn) const;
		void InternKeyCallback(MouseButton btn, MouseAction action);
		void Update();

		void SetPos(float x, float y) noexcept;;
		void SetIsScrolling(bool val) noexcept;
		void SetScroll(float scroll);
	};
}
}
