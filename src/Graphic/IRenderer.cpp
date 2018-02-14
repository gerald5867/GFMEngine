#include "IRenderer.h"

gfm::List<gfm::graphic::IRenderer*> gfm::graphic::IRenderer::s_renderers;

gfm::graphic::IRenderer::~IRenderer() noexcept {
	for(typename List<IRenderer*>::SizeType i = 0; i < s_renderers.Length(); ++i) {
		if(s_renderers[i] == this) {
			s_renderers.Remove(i);
		}
	}
}

gfm::graphic::IRenderer::IRenderer() {
	s_renderers.Append(this);
}