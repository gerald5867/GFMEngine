#include "CircleRenderer.h"
#include "Circle.h"
gfm::graphic::Circle::~Circle() noexcept {
	static int dtorcall = 0;
	CircleRenderer::instance().Remove(*this);
	m_rendererIndex = 0;
	dtorcall++;
}

gfm::graphic::Circle::Circle()
: Shape()
, m_radius(1.0f)
, m_scale(1.0f) {
	m_rendererIndex = CircleRenderer::instance().Submit(*this);
}

gfm::graphic::Circle::Circle(const Circle& other)
: Shape(other.m_position, other.m_color)
, m_radius(other.m_radius)
, m_scale(other.m_scale) {
	m_rendererIndex = CircleRenderer::instance().Submit(*this);
}


gfm::graphic::Circle::Circle(const math::Vec2& position, float radius, const math::Vec4& color) 
: Shape(position, color)
, m_radius(radius) 
, m_scale(1.0f) {
	m_rendererIndex = CircleRenderer::instance().Submit(*this);
}

gfm::graphic::Circle::Circle(float x, float y, float radius, const math::Vec4& color)
: Shape(x, y, color)
, m_radius(radius)
, m_scale(1.0f) {
	m_rendererIndex = CircleRenderer::instance().Submit(*this);
}

void gfm::graphic::Circle::SetScale(float scale) noexcept {
	m_scale = scale;
	OnChangeState();
}

void gfm::graphic::Circle::SetRadius(float radius) noexcept {
	m_radius = radius;
	OnChangeState();
}

void gfm::graphic::Circle::OnChangeState() const {
	CircleRenderer::instance().NeedUpdate(*this);
}


