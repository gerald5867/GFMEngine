#pragma once
#include "../Pipeline.h"
#ifndef GL_PIPELINE_H
#define GL_PIPELINE_H

namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {

	class GLShader;
	class GLPipeline final : public Pipeline 
	{
	public:
		virtual ~GLPipeline() noexcept;
		
		template<typename... ShaderType>
		GLPipeline(PipelineType type,ShaderType*... shaders) : Pipeline(type, shaders...) {
			//TODO STATIC ASSERT FOR SHADER TYPE!
			CreateProgram();
		}

		GLPipeline(PipelineType type);

	public:
		virtual void Create() override;
		virtual void Destroy() override;
		virtual void Bind() const noexcept override;
		virtual void Unbind() const noexcept override;
		virtual void AttachShader(const Shader* shader) override;
		virtual void DeleteAttachedShaders() noexcept override;
		
		virtual void PushUniform(const math::Matrix4x4& mat, const char* name) const override;
		virtual void BindUniformBuffer(const UniformBuffer& ubo, const char* shaderBlockName) const override;
		virtual bool ValidateUniformBuffer(const UniformBuffer& ubo) const override;

	private:
		void CheckReadyToCompile();
		void CreateProgram();
		void CheckLinkingSuccessfull();
		void ParseVertexAttributes();

		void AppendVertexAttributes(utils::uint32 locationIndex, utils::uint32& attrOffset, String&& dataType);


	private:
		utils::uint32 m_id;
		static utils::uint32 ms_currentBoundPipeline;
	};

}//GL
}//gpu
}//INTERNAL
}//gfm
#endif //GL_PIPELINE_H