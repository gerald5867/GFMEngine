#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Input/KeyboardKeys.h"
#include "../Macro/BestInline.h"

namespace gfm {
	class Application;
namespace input {

	class Keyboard
	{
	public:
		friend class Application;
	private:
		static constexpr const size_t ms_KEYARRAYSIZE = static_cast<size_t>(KeyboardKey::eKEY_MAX) + 1;
		bool m_pressedKeysThisFrame[ms_KEYARRAYSIZE];
		bool m_pressedKeysNextFrame[ms_KEYARRAYSIZE];
		bool m_pressedKeysLastFrame[ms_KEYARRAYSIZE];

		bool CheckKeyValidation(KeyboardKey key) const;

	protected:
		void InternKeyCallback(KeyboardKey key, KeyboardAction action);
		void Update();

	public:
		Keyboard();
		bool IsPressed(KeyboardKey key)const;

		bool IsDown(KeyboardKey key) const;
		bool IsUp(KeyboardKey key) const;
		bool WasDownLastFrame(KeyboardKey key) const;
		bool WasUpLastFrame(KeyboardKey key) const;

		static bool IsValidKey(KeyboardKey key) noexcept;
	};
}
}
