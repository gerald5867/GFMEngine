#pragma once
#include <utility>
#include "Keyboard.h"
namespace gfm {
namespace input {

	void Keyboard::Update() {
		std::memcpy(m_pressedKeysLastFrame, m_pressedKeysThisFrame, sizeof(bool) * ms_KEYARRAYSIZE);
		std::memcpy(m_pressedKeysThisFrame, m_pressedKeysNextFrame, sizeof(bool) * ms_KEYARRAYSIZE);
	}

	Keyboard::Keyboard() {
		std::memset(m_pressedKeysThisFrame, 0, sizeof(bool) * ms_KEYARRAYSIZE);
		std::memset(m_pressedKeysLastFrame, 0, sizeof(bool) * ms_KEYARRAYSIZE);
		std::memset(m_pressedKeysNextFrame, 0, sizeof(bool) * ms_KEYARRAYSIZE);
	}

	void Keyboard::InternKeyCallback(KeyboardKey key, KeyboardAction action) {
		switch (action) {
		case KeyboardAction::eACTION_PRESS:
			m_pressedKeysNextFrame[static_cast<size_t>(key)] = true;
			break;
		case KeyboardAction::eACTION_RELEASE:
			m_pressedKeysNextFrame[static_cast<size_t>(key)] = false;
			break;
		case KeyboardAction::eACTION_REPEAT:
			return;
		}
	}

	bool Keyboard::CheckKeyValidation(KeyboardKey key) const {
		if (!IsValidKey(key)) {
			return false;
		}
		return true;
	}

	bool Keyboard::IsDown(KeyboardKey key) const {
		if (!CheckKeyValidation(key))
			return false;
		return m_pressedKeysThisFrame[static_cast<size_t>(key)];
	}

	bool Keyboard::IsUp(KeyboardKey key) const {
		if (!CheckKeyValidation(key))
			return false;
		return !m_pressedKeysThisFrame[static_cast<size_t>(key)];
	}

	bool Keyboard::WasDownLastFrame(KeyboardKey key) const {
		if (!CheckKeyValidation(key))
			return false;
		return m_pressedKeysLastFrame[static_cast<size_t>(key)];
	}

	bool Keyboard::WasUpLastFrame(KeyboardKey key) const {
		if (!CheckKeyValidation(key))
			return false;
		return !m_pressedKeysLastFrame[static_cast<size_t>(key)];
	}

	bool Keyboard::IsPressed(KeyboardKey key) const {
		if (!CheckKeyValidation(key))
			return false;

		return m_pressedKeysLastFrame[static_cast<size_t>(key)] && m_pressedKeysThisFrame[static_cast<size_t>(key)];
	}

	 bool Keyboard::IsValidKey(KeyboardKey key) noexcept {
		 switch (key){
			case KeyboardKey::eKEY_SPACE		:
			case KeyboardKey::eKEY_APOSTROPHE	:
			case KeyboardKey::eKEY_COMMA		:
			case KeyboardKey::eKEY_MINUS		:
			case KeyboardKey::eKEY_PERIOD		:
			case KeyboardKey::eKEY_SLASH		:
			case KeyboardKey::eKEY_0			:
			case KeyboardKey::eKEY_1			:
			case KeyboardKey::eKEY_2			:
			case KeyboardKey::eKEY_3			:
			case KeyboardKey::eKEY_4			:
			case KeyboardKey::eKEY_5			:
			case KeyboardKey::eKEY_6			:
			case KeyboardKey::eKEY_7			:
			case KeyboardKey::eKEY_8			:
			case KeyboardKey::eKEY_9			:
			case KeyboardKey::eKEY_SEMICOLON	:
			case KeyboardKey::eKEY_EQUAL		:
			case KeyboardKey::eKEY_A			:
			case KeyboardKey::eKEY_B			:
			case KeyboardKey::eKEY_C			:
			case KeyboardKey::eKEY_D			:
			case KeyboardKey::eKEY_E			:
			case KeyboardKey::eKEY_F			:
			case KeyboardKey::eKEY_G			:
			case KeyboardKey::eKEY_H			:
			case KeyboardKey::eKEY_I			:
			case KeyboardKey::eKEY_J			:
			case KeyboardKey::eKEY_K			:
			case KeyboardKey::eKEY_L			:
			case KeyboardKey::eKEY_M			:
			case KeyboardKey::eKEY_N			:
			case KeyboardKey::eKEY_O			:
			case KeyboardKey::eKEY_P			:
			case KeyboardKey::eKEY_Q			:
			case KeyboardKey::eKEY_R			:
			case KeyboardKey::eKEY_S			:
			case KeyboardKey::eKEY_T			:
			case KeyboardKey::eKEY_U			:
			case KeyboardKey::eKEY_V			:
			case KeyboardKey::eKEY_W			:
			case KeyboardKey::eKEY_X			:
			case KeyboardKey::eKEY_Y			:
			case KeyboardKey::eKEY_Z			:
			case KeyboardKey::eKEY_LEFT_BRACKET	:
			case KeyboardKey::eKEY_BACKSLAH		:
			case KeyboardKey::eKEY_RIGHT_BRACKET:
			case KeyboardKey::eKEY_GRAVE_ACCENT	:
			case KeyboardKey::eKEY_WORLD_1		:
			case KeyboardKey::eKEY_WORLD_2		:
			case KeyboardKey::eKEY_ESCAPE		:
			case KeyboardKey::eKEY_ENTER		:
			case KeyboardKey::eKEY_TAB			:
			case KeyboardKey::eKEY_BACKSAPE		:
			case KeyboardKey::eKEY_INSERT		:
			case KeyboardKey::eKEY_DELETE		:
			case KeyboardKey::eKEY_RIGHT		:
			case KeyboardKey::eKEY_LEFT			:
			case KeyboardKey::eKEY_DOWN			:
			case KeyboardKey::eKEY_UP			:
			case KeyboardKey::eKEY_PAGE_UP		:
			case KeyboardKey::eKEY_PAGE_DOWN	:
			case KeyboardKey::eKEY_HOME			:
			case KeyboardKey::eKEY_END			:
			case KeyboardKey::eKEY_CAPS_LOCK	:
			case KeyboardKey::eKEY_SCROLL_LOCK	:
			case KeyboardKey::eKEY_NUM_lOCK		:
			case KeyboardKey::eKEY_PRINT_SCREEN	:
			case KeyboardKey::eKEY_PAUSE		:
			case KeyboardKey::eKEY_F1			:
			case KeyboardKey::eKEY_F2			:
			case KeyboardKey::eKEY_F3			:
			case KeyboardKey::eKEY_F4			:
			case KeyboardKey::eKEY_F5			:
			case KeyboardKey::eKEY_F6			:
			case KeyboardKey::eKEY_F7			:
			case KeyboardKey::eKEY_F8			:
			case KeyboardKey::eKEY_F9			:
			case KeyboardKey::eKEY_F10			:
			case KeyboardKey::eKEY_F11			:
			case KeyboardKey::eKEY_F12			:
			case KeyboardKey::eKEY_F13			:
			case KeyboardKey::eKEY_F14			:
			case KeyboardKey::eKEY_F15			:
			case KeyboardKey::eKEY_F16			:
			case KeyboardKey::eKEY_F17			:
			case KeyboardKey::eKEY_F18			:
			case KeyboardKey::eKEY_F19			:
			case KeyboardKey::eKEY_F20			:
			case KeyboardKey::eKEY_F21			:
			case KeyboardKey::eKEY_F22			:
			case KeyboardKey::eKEY_F23			:
			case KeyboardKey::eKEY_F24			:
			case KeyboardKey::eKEY_F25			:
			case KeyboardKey::eKEY_KP_0			:
			case KeyboardKey::eKEY_KP_1			:
			case KeyboardKey::eKEY_KP_2			:
			case KeyboardKey::eKEY_KP_3			:
			case KeyboardKey::eKEY_KP_4			:
			case KeyboardKey::eKEY_KP_5			:
			case KeyboardKey::eKEY_KP_6			:
			case KeyboardKey::eKEY_KP_7			:
			case KeyboardKey::eKEY_KP_8			:
			case KeyboardKey::eKEY_KP_9			:
			case KeyboardKey::eKEY_KP_DECIMAL	:
			case KeyboardKey::eKEY_KP_DIVIDE	:
			case KeyboardKey::eKEY_KP_MULTIPLY	:
			case KeyboardKey::eKEY_KP_SUBTRACT	:
			case KeyboardKey::eKEY_KP_ADD		:
			case KeyboardKey::eKEY_KP_ENTER		:
			case KeyboardKey::eKEY_KP_EQUAL		:
			case KeyboardKey::eKEY_LEFT_SHIFT	:
			case KeyboardKey::eKEY_LEFT_CONTROL	:
			case KeyboardKey::eKEY_LEFT_ALT		:
			case KeyboardKey::eKEY_LEFT_SUPER	:
			case KeyboardKey::eKEY_RIGHT_SHIFT	:
			case KeyboardKey::eKEY_RIGHT_CONTROL:
			case KeyboardKey::eKEY_RIGHT_ALT	:
			case KeyboardKey::eKEY_RIGHT_SUPER	:
			case KeyboardKey::eKEY_MENU			:
				return true;
		 }
		 return false;
	}
}
}