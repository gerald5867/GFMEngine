#pragma once
#ifndef CIRCLE_RENDERER_H
#define CIRCLE_RENDERER_H
#include "IRenderer2D.h"
#include "../Macro/ApiCall.h"
#include "../GPUApi/VertexBufferLayout.h"
#include "../Memory/UniquePointer.h"

namespace gfm {
namespace INTERNAL {
namespace gpu {

	class VertexBuffer;
	class IndexBuffer;
	class PipelineLayout;
	class UniformBuffer;
}//gpu
}//INTERNAL

namespace graphic {
	class Circle;

	GFM_APICALL struct alignas(16) CircleUniformData {
		math::Vec4 color;
		math::Vec2 position;
		float radius;
		float scale;
	};

	GFM_APICALL struct CircleVertexData {
		math::Vec2 vertex;
		math::Vec2 textureCoordiantes;
	};

class GFM_APICALL CircleRenderer : public IRenderer2D, public policy::MakeSingletonStatic<CircleRenderer> {
	private:
		friend class Circle;
	public:
		CircleRenderer();
		virtual ~CircleRenderer() noexcept;

	public:
		virtual void Update() override;
		virtual void Render() override;

		utils::uint32 Submit(const Circle& circle);
		void Remove(const Circle& circle);
		void NeedUpdate(const Circle& circle);
		
	private:
		void FillIndexBuffer();
		void FillVertexBuffer();
		void CreateVertexBufferLayout();

	private:
		static constexpr const utils::uint32 s_CIRCLEMAXCOUNT = 300;
		static constexpr const utils::uint32 s_CIRCLEVERTEXPRECISION = 128;
		static constexpr const utils::uint32 s_UINFORMBUFFERMAXSIZE = s_CIRCLEMAXCOUNT * sizeof(CircleUniformData);
		static constexpr const char* const s_UNIFORMBLOCKNAME = "ubo_circle";

	private:
		List<utils::uint32> m_toRemoveCircels;
		List<const Circle*> m_toUpdateCircels;
		List<utils::uint32> m_freeCircleIndices;
		utils::uint32 m_CircleDrawCount;

		INTERNAL::gpu::VertexBufferLayout m_vertexBufferLayout;
		memory::UniquePointer<INTERNAL::gpu::VertexBuffer> m_vertexBuffer;
		memory::UniquePointer<INTERNAL::gpu::IndexBuffer> m_indexBuffer;
		memory::UniquePointer<INTERNAL::gpu::UniformBuffer> m_uniformBuffer;
		memory::UniquePointer<INTERNAL::gpu::PipelineLayout> m_pipelineLayout;
};

}//graphic
}//gfm

#endif // CIRCLE_RENDERER_H