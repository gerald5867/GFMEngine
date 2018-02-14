#pragma once
#ifndef GRAPHIC_OBJECT_FACTORY_H
#define GRAPHIC_OBJECT_FACTORY_H
#include "Pipeline.h"
#include "../Memory/DefaultAllocator.h"
#include "../Memory/UniquePointer.h"
#include "../Policys/Singleton.h"
#include "GraphicAPI.h"
namespace gfm {
namespace INTERNAL {
namespace gpu {

	class VertexBuffer;
	class IndexBuffer;
	class PipelineLayout;
	class UniformBuffer;
	enum class BufferUsage;

	class GraphicObjectFactory final : public policy::MakeSingletonPtr<GraphicObjectFactory>
	{
		public:
			static GraphicObjectFactory& Initialize(GraphicAPI usedAPI);
			static void Destroy() noexcept;

		public:

			memory::UniquePointer<VertexBuffer> CreateVertexBuffer(BufferUsage usage) const;
			memory::UniquePointer<IndexBuffer> CreateIndexBuffer(BufferUsage usage) const;
			memory::UniquePointer<UniformBuffer> CreateUniformBuffer(BufferUsage usage) const;
			memory::UniquePointer<PipelineLayout> CreatePipelineLayout() const;

		private:
			GraphicObjectFactory(GraphicObjectFactory&&)				  = delete;
			GraphicObjectFactory(const GraphicObjectFactory&)			  = delete;
			GraphicObjectFactory& operator =(const GraphicObjectFactory&) = delete;
			GraphicObjectFactory& operator =(GraphicObjectFactory&&)      = delete;
			GraphicObjectFactory() = default;

		private:
			memory::DefaultAllocator m_allocator;
			GraphicAPI m_API = GraphicAPI::eNONE;
	};
}//INTERNAL
}//graphic
}//gfm
#endif //GRAPHIC_OBJECT_FACTORY_H 