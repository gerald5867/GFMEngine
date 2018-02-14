#pragma once
#ifndef RENDERER_2D_H
#define RENDERER_2D_H
#include "IRenderer.h"
#include "../Macro/ApiCall.h"
#include "..\Utils\Types.h"
#include "..\Math\Matrix.h"
#include "..\Math\Vector.h"

namespace gfm {
namespace graphic {


class GFM_APICALL IRenderer2D : public IRenderer {
	public:
		IRenderer2D(utils::uint32 width, utils::uint32 height, const math::Mat4& projectionMatrix);
		virtual ~IRenderer2D() noexcept = default;

	public:
		void UpdateProjectionMatrix(const math::Mat4& projectionMatrix);
		void UpdateViewport(utils::uint32 width, utils::uint32 height);
		void UpdateViewport(const math::Vec2& windowSize);

	protected:
		static constexpr const char* const s_PROJECTIONMATRIXNAME = "u_projectionMatrix";
		static constexpr const char* const s_VIEWMATRIXNAME = "u_viewMatrix";

	protected:
		utils::uint32 m_windowWidth;
		utils::uint32 m_windowHeight;
		math::Mat4 m_projectionMatrix;

	//uniform buffer for colors
	//abstract camera pointer for camera if want

};

}//graphic
}//gfm
#endif //RENDERER_2D_H