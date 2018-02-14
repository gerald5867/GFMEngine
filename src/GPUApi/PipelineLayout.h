#pragma once
#include "../DataStructures/List.h"
#include "../Macro/BestInline.h"
#include "../Utils/Types.h"
#include "PipelineType.h"
#ifndef PIPELINE_LAYOUT_H
#define PIPELINE_LAYOUT_H
namespace gfm {
namespace INTERNAL {
namespace gpu {

	struct VertexAttribute;
	class VertexBufferLayout;
	class Buffer;
	class Pipeline;
	class PipelineLayout 
	{
		public:
			virtual void CreateFromPipeline(PipelineType type) = 0;
			virtual void CreateFromPipeline(const Pipeline& pipeline) = 0;
			virtual void AppendBuffer(const Buffer& buffer) = 0;
			virtual void EnableVertexAttribute(const VertexAttribute& attribute, utils::uint32 stride) = 0;
			virtual void CreateFromVertexBufferLayout(const VertexBufferLayout& layout) = 0;
			virtual void Bind() const noexcept = 0;
			virtual void Unbind() const noexcept = 0;
			GFM_BEST_INLINE PipelineType GetAssoiciatedPipelineType() const noexcept { return m_pipelineType; }

			virtual ~PipelineLayout() noexcept = default;
		protected:
			PipelineType m_pipelineType = PipelineType::eNONE;
			List<const Buffer*> m_buffers;
	};

}//gpu
}//INTERNAL
}//gfm
#endif // PIPELINE_LAYOUT_H