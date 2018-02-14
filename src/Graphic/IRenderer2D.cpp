#include "IRenderer2D.h"
#include "..\GPUApi\GraphicCommandHandler.h"

gfm::graphic::IRenderer2D::IRenderer2D(utils::uint32 width, utils::uint32 height, const math::Mat4& projectionMatrix) 
: m_windowWidth(width)
, m_windowHeight(height)
, m_projectionMatrix(projectionMatrix) {
}

void gfm::graphic::IRenderer2D::UpdateProjectionMatrix(const math::Mat4& projectionMatrix) {
	m_projectionMatrix = projectionMatrix;
}

void gfm::graphic::IRenderer2D::UpdateViewport(utils::uint32 width, utils::uint32 height) {
	m_windowWidth = width;
	m_windowHeight = height;
	INTERNAL::gpu::GraphicCommandHandler::Instance().UpdateViewport(width, height);
}

void gfm::graphic::IRenderer2D::UpdateViewport(const math::Vec2& windowSize) {
	m_windowWidth = static_cast<utils::uint32>(windowSize.x);
	m_windowHeight = static_cast<utils::uint32>(windowSize.y);
	UpdateViewport(m_windowWidth, m_windowHeight);
}
