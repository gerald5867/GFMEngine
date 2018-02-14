#pragma once
#include "../DataStructures/List.h"
#include "../Policys/Singleton.h"
#include "../DataStructures/Array.h"
#include "PipelineType.h"
#ifndef PIPELINE_MANAGER_H
#define PIPELINE_MANAGER_H
namespace gfm {
namespace INTERNAL {
namespace gpu {

	class VertexBuffer;
	class IndexBuffer;
	class Pipeline;

	enum class BufferUsage;
	enum class GraphicAPI;

	class PipelineManager final : public policy::MakeSingletonPtr<PipelineManager>
	{
		public:
			static gfm::INTERNAL::gpu::PipelineManager& Initialize(GraphicAPI usedApi);
			static void Destroy() noexcept;
	
		public:
			const Pipeline& GetPipeline(PipelineType type) const noexcept;
			void InitializeGLPipelines();

		private:
			PipelineManager() = default;
	
		private:
			static constexpr const utils::uint32 ms_PIPELINECOUNT = static_cast<utils::uint32>(PipelineType::eMAX_NUM);
			
			utils::uint32 m_lastPipelineIndex = 0;
			Array<Pipeline*, ms_PIPELINECOUNT> m_pipelines;
	};
}// gpu
}//INTERNAL
}//gfm
#endif // PIPELINE_MANAGER_H