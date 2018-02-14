#pragma once
#ifndef IRENDERER_H
#define IRENDERER_H
#include "../Application.h"
#include "../Macro/ApiCall.h"
namespace gfm {
class Application;
namespace graphic {

class GFM_APICALL IRenderer {
		friend class Application;
	public:
		virtual ~IRenderer() noexcept;
		IRenderer();

	public:
		virtual void Update() = 0;
		virtual void Render() = 0;

	private:
		static List<IRenderer*> s_renderers;
};

}//graphic
}//gfm
#endif //IRENDERER_H