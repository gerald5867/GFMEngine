#pragma once
#include "GL/GLShader.h"
#include "GL/Shader/ShaderSource.h"
#include "PipelineManager.h"
#include "GraphicAPI.h"
#include "../Memory/DefaultAllocator.h"
#include "../Memory/UniquePointer.h"
#include "../TypeTraits/ArrayFunc.h"
#include "GL/GLPipeline.h"
gfm::INTERNAL::gpu::PipelineManager* gfm::policy::MakeSingletonPtr<gfm::INTERNAL::gpu::PipelineManager>::mp_instance = nullptr;

gfm::INTERNAL::gpu::PipelineManager& gfm::INTERNAL::gpu::PipelineManager::Initialize(GraphicAPI usedApi) {
	if(mp_instance != nullptr) {
		return *mp_instance;
	}
	mp_instance = reinterpret_cast<PipelineManager*>(memory::DefaultAllocator::Allocate(sizeof(PipelineManager)));
	new (mp_instance) PipelineManager();
	switch (usedApi)
	{
	case GraphicAPI::eOPENGL:
		mp_instance->InitializeGLPipelines();
		break;
	}
	return *mp_instance;
}

void gfm::INTERNAL::gpu::PipelineManager::InitializeGLPipelines() {
	using namespace memory;//for Allocators
	GL::GLShader vert(ShaderType::eVERTEX);
	GL::GLShader frag(ShaderType::eFRAGMENT);
	static constexpr const auto cPIPELINEMAX = static_cast<utils::uint32>(PipelineType::eMAX_NUM);
	static constexpr const auto cSHADERCOUNT = traits::ArrayLen(GL::ShaderSource::ShaderCode);
	static_assert(cPIPELINEMAX * 2 == cSHADERCOUNT, "There must be two Shaders per Pipeline!");
	for (utils::uint32 i = 0; i <= cPIPELINEMAX; i += 2) {
		vert.CreateFromSource(GL::ShaderSource::ShaderCode[i]);
		frag.CreateFromSource(GL::ShaderSource::ShaderCode[i + 1]);
		Pipeline*& pipeline = mp_instance->m_pipelines[mp_instance->m_lastPipelineIndex++];
		PipelineType type = static_cast<PipelineType>(i);
		pipeline = (DefaultAllocator::AllocateObject<GL::GLPipeline>(type, &vert, &frag));
		pipeline->Create();
	}
	vert.Destroy();
	frag.Destroy();
}

void gfm::INTERNAL::gpu::PipelineManager::Destroy() noexcept {
	for(auto i = 0U; i < mp_instance->m_lastPipelineIndex; ++i) {
		mp_instance->m_pipelines[i]->Destroy();
	}
	//deallocate pipelines
}

const gfm::INTERNAL::gpu::Pipeline& gfm::INTERNAL::gpu::PipelineManager::GetPipeline(PipelineType type) const noexcept {
	GFM_DEBUG_ASSERT(!(type < PipelineType::eSTART_NUM || type >= PipelineType::eMAX_NUM), GFM_STRING("GetPipeline type out of Range!"));
	return *m_pipelines[static_cast<utils::uint32>(type)];
}

