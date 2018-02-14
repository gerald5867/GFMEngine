#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gfm
{
namespace input
{

	enum class MouseAction {
		eACTION_PRESS	= GLFW_PRESS,
		eACTION_RELEASE = GLFW_RELEASE
	};

	enum class MouseButton {
		eBUTTON_LEFT   = GLFW_MOUSE_BUTTON_LEFT,
		eBUTTON_RIGHT  = GLFW_MOUSE_BUTTON_RIGHT,
		eBUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
		eBUTTON_4      = GLFW_MOUSE_BUTTON_4,
		eBUTTON_5      = GLFW_MOUSE_BUTTON_5,
		eBUTTON_6      = GLFW_MOUSE_BUTTON_6,
		eBUTTON_7      = GLFW_MOUSE_BUTTON_7,
		eBUTTON_8      = GLFW_MOUSE_BUTTON_8,
		eBUTTON_LAST   = GLFW_MOUSE_BUTTON_LAST,
	};
}
}
