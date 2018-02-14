#pragma once
#include "Rectangle.h"
#include "RectangleRenderer.h"

gfm::graphic::Rectangle::~Rectangle() noexcept {
	RectangleRenderer::instance().Remove(*this);
	m_rendererIndex = 0;
}

gfm::graphic::Rectangle::Rectangle()
: Shape(0, 0, math::Vec4(1.0f, 0.0f, 0.0f, 1.0f))
, m_size(0.0f, 0.0f) {
	m_rendererIndex = RectangleRenderer::instance().Submit(*this);
}

gfm::graphic::Rectangle::Rectangle(const Rectangle& other) 
: Shape(other.m_position, other.m_color)
, m_size(other.m_size)
, m_rotation(other.m_rotation) {
	m_rendererIndex = RectangleRenderer::instance().Submit(*this);
}

gfm::graphic::Rectangle::Rectangle(float x, float y, float width, float height, const math::Vec4& color) 
: Shape(x, y, color)
, m_width(width)
, m_height(height) { 
	m_rendererIndex = RectangleRenderer::instance().Submit(*this);
}

gfm::graphic::Rectangle::Rectangle(const math::Vec2& position, float width, float height, const math::Vec4& color) 
: Shape(position.x, position.y, color)
, m_width(width)
, m_height(height) {
	m_rendererIndex = RectangleRenderer::instance().Submit(*this);
}

gfm::graphic::Rectangle::Rectangle(float x, float y, const math::Vec2& size, const math::Vec4& color) 
: Shape(x, y, color)
, m_size(size) {
	m_rendererIndex = RectangleRenderer::instance().Submit(*this);
}

gfm::graphic::Rectangle::Rectangle(const math::Vec2& position, const math::Vec2& size, const math::Vec4& color) 
: Shape(position.x, position.y, color)
, m_size(size) {
	m_rendererIndex = RectangleRenderer::instance().Submit(*this);
}

const gfm::math::Vec2& gfm::graphic::Rectangle::GetSize() const noexcept {
	return m_position;
}

float gfm::graphic::Rectangle::GetWidth() const noexcept {
	return m_width;
}

float gfm::graphic::Rectangle::GetHeight() const noexcept {
	return m_height;
}

void gfm::graphic::Rectangle::SetSize(const math::Vec2& position) noexcept {
	m_position = position;
	OnChangeState();
}

void gfm::graphic::Rectangle::SetSize(float width, float height) noexcept {
	m_width = width;
	m_height = height;
	OnChangeState();
}

void gfm::graphic::Rectangle::SetWidth(float width) noexcept {
	m_width = width;
	OnChangeState();
}

void gfm::graphic::Rectangle::SetHeight(float height) noexcept {
	m_height = height;
	OnChangeState();
}

void gfm::graphic::Rectangle::Rotate(utils::int32 degrees) noexcept {
	m_rotation = degrees;
}

gfm::math::Vec2 gfm::graphic::Rectangle::LefTop() const noexcept {
	return m_position;
}

gfm::math::Vec2 gfm::graphic::Rectangle::RightTop() const noexcept {
	return {m_x + m_width, m_y};
}

gfm::math::Vec2 gfm::graphic::Rectangle::RightBottom() const noexcept {
	return {m_x + m_width, m_y + m_height};
}

gfm::math::Vec2 gfm::graphic::Rectangle::LeftBottom() const noexcept {
	return {m_x, m_y + m_height};
}

void gfm::graphic::Rectangle::SetScale(float scale) noexcept {
	m_position *= scale;
	OnChangeState();
}

void gfm::graphic::Rectangle::OnChangeState() const {
	RectangleRenderer::instance().NeedUpdate(*this);
}


