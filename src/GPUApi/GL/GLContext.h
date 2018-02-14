#pragma once
#ifndef GL_CONTEXT_H__
#define GL_CONTEXT_H__
#include "../Context.h"
#include "../GraphicAPI.h"
namespace gfm {
namespace input {
	class Window;
}
namespace INTERNAL {
namespace gpu {
namespace GL {

	class GLContext final : public Context 
	{
	public:
		explicit GLContext(GraphicAPI api, input::Window& targetWindow);
		virtual ~GLContext();
	};
}
}
}
}
#endif // GL_CONTEXT_H__