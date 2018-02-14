#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include "../Macro/ApiCall.h"
#include "../Math/Vector.h"
#include "../Utils/Types.h"
#include "../Math/Matrix.h"
#include "../Utils/Types.h"
#include "Color.h"
//TODO: SEPERATE INTO CPP
namespace gfm {
namespace graphic {

	class GFM_APICALL Shape {
		public:
			virtual ~Shape() noexcept = default;
			Shape()	= default;
	
			Shape(const Shape&)			    = default;
			Shape(Shape&&)                  = default;
			Shape& operator =(const Shape&) = default;
			Shape& operator =(Shape&&)      = default;
	
			Shape(float x, float y, const math::Vec4& color, bool show = true) 
			: m_x(x)
			, m_y(y)
			, m_show(show)
			, m_color(color) {
			}

			Shape(const math::Vec2& position, const math::Vec4& color, bool show = true) 
			: m_position(position)
			, m_show(show)
			, m_color(color) {
			}
		
		public:
			GFM_BEST_INLINE const math::Vec2& GetPosition() const noexcept { return m_position; }
			GFM_BEST_INLINE float GetX() const noexcept { return m_x; }
			GFM_BEST_INLINE float GetY() const noexcept { return m_y; }
			GFM_BEST_INLINE math::Vec4 GetColor() const noexcept { return m_color;  }
			
			GFM_BEST_INLINE void Show() noexcept { 
				m_show = true; 
				OnChangeState();
			}

			GFM_BEST_INLINE void Hide() noexcept { 
				m_show = false; 
				OnChangeState();
			}

			GFM_BEST_INLINE bool IsShow() const noexcept {
				return m_show;
			}

			GFM_BEST_INLINE void SetPosition(const math::Vec2& position) { 
				m_position = position;
				OnChangeState();
			}

			GFM_BEST_INLINE void SetPosition(float x, float y) {
				m_x = x;
				m_y = y;
				OnChangeState();
			}

			GFM_BEST_INLINE void SetX(float x) { 
				m_x = x;
				OnChangeState();
			}

			GFM_BEST_INLINE void SetY(float y) { 
				m_y = y;
				OnChangeState();
			}

			GFM_BEST_INLINE void SetColor(const math::Vec4& color) {
				m_color = color;
				OnChangeState();
			}

		protected:
			virtual void OnChangeState() const = 0;

		protected:
			union {
				struct {
					float m_x;
					float m_y;
				};
				math::Vec2 m_position;
			};
			bool m_show = true;
			math::Vec4 m_color = { 1.0f, 0.0f, 0.0f, 1.0f };
	};
}//namespace graphic
}//namespace gfm
#endif // SHAPE_H