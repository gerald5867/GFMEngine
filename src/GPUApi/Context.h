#pragma once
#include "../Macro/BestInline.h"
#include "GraphicAPI.h"
#ifndef CONTEXT_H
#define CONTEXT_H

namespace gfm {
namespace input {
	class Window;
}
namespace INTERNAL {
namespace gpu {
	class Context 
	{
		public:
			static Context& Initialize(GraphicAPI api, input::Window& targetWindow);
			static Context& Instance();
			static void Destroy() noexcept;
			
		public:
			virtual ~Context() noexcept = default;
			GFM_BEST_INLINE GraphicAPI GetAPI() const noexcept { return m_API; }

		protected:
			Context() = default;

		protected:
			static Context* mp_instance;
			GraphicAPI m_API = GraphicAPI::eNONE;
	};
}
}
}
#endif // CONTEXT_Hs
