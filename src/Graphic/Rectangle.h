#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include "../Macro/ApiCall.h"
#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Utils/Types.h"
//TODO: implement operators
//TODO: implement rotate
//TODO: implement IRenderer2D ptr and if its not nullptr use it otherwise default renderer
//TODO: implement textures
//TODO: MOVE OPERATOR MOVE ASSIGMENT COPY ASSIGMENT !
//TODO: COLOR CLASS AND OVERLOAD SETCOLOR
namespace gfm {
namespace graphic {

	class RectangleRenderer;

	class GFM_APICALL Rectangle : public Shape {
			friend class RectangleRenderer;
		public:
			virtual ~Rectangle() noexcept;
			Rectangle();
			Rectangle(const Rectangle& other);
			Rectangle(float x, float y, float width, float height, const math::Vec4& color);
			Rectangle(const math::Vec2& position, const math::Vec2& size, const math::Vec4& color);
			Rectangle(float x, float y, const math::Vec2& size, const math::Vec4& color);
			Rectangle(const math::Vec2& position, float width, float height, const math::Vec4& color);

		public:
			void SetScale(float scale) noexcept;
			virtual void OnChangeState() const override;

		public:
			const math::Vec2& GetSize() const noexcept;
			float GetWidth() const noexcept;
			float GetHeight() const noexcept;

			void SetSize(const math::Vec2& position) noexcept;
			void SetSize(float width, float height) noexcept;
			void SetWidth(float width) noexcept;
			void SetHeight(float height) noexcept;

			void Rotate(utils::int32 degrees) noexcept;
		private:
			math::Vec2 LefTop() const noexcept;
			math::Vec2 RightTop() const noexcept;
			math::Vec2 RightBottom() const noexcept;
			math::Vec2 LeftBottom() const noexcept;

		protected:
			union  {
				struct {
					float m_width;
					float m_height;
				};
				math::Vec2 m_size;
			};
			mutable utils::uint32 m_rendererIndex = 0;
			mutable utils::uint32 m_updateListIndex = 0;
			utils::int32 m_rotation;
			
	};
}//namespace graphic
}//namespace gfm
#endif // RECTANGLE_H
