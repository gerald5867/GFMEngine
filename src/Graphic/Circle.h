#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#include "../Macro/ApiCall.h"
#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Utils/Types.h"
//implement operators
//implement textures
//TODO: implement IRenderer2D ptr and if its not nullptr use it otherwise default renderer
//TODO: MOVE OPERATOR MOVE ASSIGMENT COPY ASSIGMENT !
//TODO: COLOR CLASS AND OVERLOAD SETCOLOR
namespace gfm {
namespace graphic {

	class CircleRenderer;

class GFM_APICALL Circle : public Shape {
		friend class CircleRenderer;
	public:
		virtual ~Circle() noexcept;
		Circle();
		Circle(const Circle& other);
		Circle(float x, float y, float radius, const math::Vec4& color);
		Circle(const math::Vec2& position, float radius, const math::Vec4& color);

	public:
		void SetScale(float scale) noexcept;
		void SetRadius(float radius) noexcept;

		virtual void OnChangeState() const override;

	protected:
		float m_radius;
		float m_scale;
		mutable utils::uint32 m_rendererIndex = 0;
		mutable utils::uint32 m_updateListIndex = 0;
};
}//namespace graphic
}//namespace gfm
#endif // CIRCLE_H
