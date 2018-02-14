#pragma once
#include <utility>
#include "Mouse.h"


namespace gfm
{
namespace input
{
	Mouse::Mouse(){
		memset(this, 0, sizeof(*this) - sizeof(bool) - sizeof(CallbackFuncPtr));
	}

	void Mouse::SetPos(float x, float y) noexcept{
		m_xThisFrame = x;
		m_yThisFrame = y;
	}

	void Mouse::SetIsScrolling(bool val) noexcept{
		m_isScrolling = val;
	}

	void Mouse::SetScroll(float scroll){
		m_isScrolling = true;
		m_scrollNextFrame = scroll;
	}

	bool Mouse::IsValidButton(MouseButton btn) noexcept{
		switch (btn){
			case MouseButton::eBUTTON_LEFT:
			case MouseButton::eBUTTON_RIGHT:
			case MouseButton::eBUTTON_MIDDLE:
			case MouseButton::eBUTTON_4:
			case MouseButton::eBUTTON_5:
			case MouseButton::eBUTTON_6:
			case MouseButton::eBUTTON_7:
			case MouseButton::eBUTTON_8:
				return true;
		}
		return false;
	}

	float Mouse::GetX()  const noexcept{
		return m_xThisFrame;
	}

	float Mouse::GetY()  const noexcept{
		return m_yThisFrame;
	}

	math::Vec2 Mouse::GetLastFramePosition()  const noexcept{
		return { GetLastFrameX(), GetLastFrameY() };
	}

	float Mouse::GetLastFrameX()  const noexcept{
		return m_xLastFrame;
	}

	float Mouse::GetLastFrameY()  const noexcept{
		return m_yLastFrame;
	}

	math::Vec2 Mouse::GetPosition()  const noexcept{
		return { GetX(), GetY() };
	}

	float Mouse::GetDeltaX() const noexcept{
		return m_xThisFrame - m_xLastFrame;
	}

	float Mouse::GetDeltaY() const noexcept{
		return m_yThisFrame - m_yLastFrame;
	}

	math::Vec2 Mouse::GetDeltaPosition() const noexcept{
		return { GetDeltaX(), GetDeltaY() };
	}

	bool Mouse::CheckButtonValidation(MouseButton btn) const{
		if (!IsValidButton(btn)){
			return false;
		}
		return true;
	}

	void Mouse::SetCallback(CallbackFuncPtr func){
		m_otherCallback = func;
	}

	bool Mouse::IsScrollingIn() const{
		return m_isScrolling && m_scrollLastFrame < 0 && m_scrollThisFrame < 0;
	}

	bool Mouse::IsScrollingOut() const{
		return m_isScrolling && m_scrollLastFrame > 0 && m_scrollThisFrame > 0;
	}

	bool Mouse::IsPressed(MouseButton btn)const{
		if (!CheckButtonValidation(btn)) {
			return false;
		}

		return m_pressedButtonsLastFrame[static_cast<size_t>(btn)] && m_pressedButtonsThisFrame[static_cast<size_t>(btn)];
	
	}

	bool Mouse::WasUpLastFrame(MouseButton btn) const{
		if (!CheckButtonValidation(btn)) {
			return false;
		}
		return !m_pressedButtonsLastFrame[static_cast<size_t>(btn)];
	}

	bool Mouse::WasDownLastFrame(MouseButton btn) const{
		if (!CheckButtonValidation(btn)) {
			return false;
		}
		return m_pressedButtonsLastFrame[static_cast<size_t>(btn)];
	}

	bool Mouse::IsUp(MouseButton btn)const{
		if (!CheckButtonValidation(btn)) {
			return false;
		}
		return !m_pressedButtonsThisFrame[static_cast<size_t>(btn)];
	}

	bool Mouse::IsDown(MouseButton btn) const{
		if (!CheckButtonValidation(btn)) {
			return false;
		}
		return m_pressedButtonsThisFrame[static_cast<size_t>(btn)];
	}

	void Mouse::Update(){
		m_scrollLastFrame = m_scrollThisFrame;
		m_scrollThisFrame = m_scrollNextFrame;

		m_xLastFrame = m_xThisFrame;
		m_yLastFrame = m_yThisFrame;

		std::memcpy(m_pressedButtonsLastFrame, m_pressedButtonsThisFrame, sizeof(bool) * ms_BUTTONARRAYSIZE);
		std::memcpy(m_pressedButtonsThisFrame, m_pressedButtonsNextFrame, sizeof(bool) * ms_BUTTONARRAYSIZE);
	}

	void Mouse::InternKeyCallback(MouseButton btn, MouseAction action){
		if (m_otherCallback != nullptr)
			m_otherCallback(btn, action);

		switch (action)
		{
		case MouseAction::eACTION_PRESS:
			m_pressedButtonsNextFrame[static_cast<size_t>(btn)] = true;
			break;

		case MouseAction::eACTION_RELEASE:
			m_pressedButtonsNextFrame[static_cast<size_t>(btn)] = false;
			break;
		}
	}
}
}