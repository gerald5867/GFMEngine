#pragma once
#include "../Macro/ApiCall.h"
#include "../Math/Vector.h"
#include "../DataStructures/Array.h"
#include "../Policys/Singleton.h"
#include "Color.h"
#include "../GPUApi/VertexBufferLayout.h"
#include "../DataStructures/List.h"
#include "../Math/Matrix.h"
#include "IRenderer2D.h"
#include "../Memory/UniquePointer.h"
#ifndef RECTANGLE_RENDERER_H
#define RECTANGLE_RENDERER_H

// TODO: USE A UNIFORM BUFFER FOR THE COLORS AND MAKE COLORS 4 Byte
// TODO: PASS WIDTH AND HEIGHT TO CTOR AND MAKE A UPDATE FUNCTION FOR IT
// TODO: MAKE EASY THING TO SET VERTEX ATTRIBUTES MANENUEL
// TODO: CUT OFF THE SINGLETON
namespace gfm {
namespace INTERNAL {
namespace gpu {

	class VertexBuffer;
	class IndexBuffer;
	class PipelineLayout;
}// gpu
}//INTERNAL
namespace graphic {

	class Rectangle;

	GFM_APICALL struct RectangleVertexData {
		math::Vec2 vertex;
		utils::uint32 color;
	};

	class GFM_APICALL RectangleRenderer : public IRenderer2D, public policy::MakeSingletonStatic<RectangleRenderer> {
		public:
			RectangleRenderer();
			virtual ~RectangleRenderer() noexcept;

		public:
			virtual void Update() override;
			virtual void Render() override;
			utils::uint32 Submit(const Rectangle& rectanlge);
			void Remove(const Rectangle& rectangle);
			void NeedUpdate(const Rectangle& rectangle);


		private:			
			void FillIndexBuffer() const;
			void CreateVertexBufferLayout();

		private:
			static const constexpr utils::uint32 s_RECTANGLEMAXCOUNT = 60000;
			static const constexpr utils::uint32 s_RECTANGLESIZE = sizeof(RectangleVertexData) * 4;
			static const constexpr utils::uint32 s_RECTANGLEVERTEXBUFFERSIZE = s_RECTANGLESIZE * s_RECTANGLEMAXCOUNT;
			static const constexpr utils::uint32 s_RECTANGLEINDEXBUFFERLENGTH = s_RECTANGLEMAXCOUNT * 6;

		private:
			List<utils::uint32> m_toRemoveRectangles;
			List<const Rectangle*> m_toUpdateRectangles;
			List<utils::uint16> m_freeRectangleIndices;
			utils::uint32 m_rectangleDrawCount;
			
			INTERNAL::gpu::VertexBufferLayout m_vertexBufferLayout;
			mutable memory::UniquePointer<INTERNAL::gpu::IndexBuffer> m_indexBuffer;
			memory::UniquePointer<INTERNAL::gpu::VertexBuffer> m_vertexBuffer;
			memory::UniquePointer<INTERNAL::gpu::PipelineLayout> m_pipelineLayout;
			//uniform buffer for colors
			//abstract camera pointer for camera if want
	};

}//graphic
}//gfm
#endif //RECTANGLE_RENDERER_H