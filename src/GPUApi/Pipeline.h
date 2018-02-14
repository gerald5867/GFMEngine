#pragma once
#ifndef PIPELINE_H
#define PIPELINE_H
#include <utility>
#include "BufferType.h"
#include "BufferUsage.h"
#include "ShaderType.h"
#include "Buffer.h"
#include "VertexAttribute.h"
#include "../DataStructures/List.h"
#include "../Algorithm/All.h"
#include "../Utils/Types.h"

namespace gfm {
namespace math {
	struct Matrix4x4;
}//math
namespace INTERNAL {
namespace gpu {

	class Shader;
	class UniformBuffer;
	class Pipeline {
		public:
			virtual ~Pipeline() noexcept = default;
	
		protected:
			Pipeline(PipelineType type) : m_type(type) {
			}

			template<typename... ShaderTypes>
			Pipeline(PipelineType type, ShaderTypes*... shaders) : m_type(type) {
				std::memset(m_AttachedShader, 0, sizeof(const Shader*) * static_cast<utils::uint32>(ShaderIndex::eSHADER_INDEX_MAXNUM));
				static const constexpr bool AllShaders[] = {
					(std::is_same<Shader*, typename std::decay<decltype(shaders)>::type>::value 
					|| std::is_same<const Shader*, typename std::decay<decltype(shaders)>::type>::value)...};
				//static_assert(algorithm::All(AllShaders, sizeof...(ShaderTypes)), "Pipeline only Accepts Shaders! wrong type passed!");
				const Shader* shaderArgs[] = {shaders...};
				for(auto i = 0U; i < sizeof(shaderArgs) / sizeof(const Shader*); ++i) {
					m_AttachedShader[i] = shaderArgs[i];
				}
			}
	
		public:
			virtual void Create() = 0;
			virtual void Destroy() = 0;
			virtual void Bind() const noexcept = 0;
			virtual void Unbind() const noexcept = 0;
	
			virtual void AttachShader(const Shader* shader) = 0;
			virtual void PushUniform(const math::Matrix4x4& mat, const char* name) const = 0;

			virtual void BindUniformBuffer(const UniformBuffer& ubo, const char* shaderBlockName) const = 0;
			virtual bool ValidateUniformBuffer(const UniformBuffer& ubo) const = 0;

			GFM_BEST_INLINE void AppendVertexAttribute(const VertexAttribute& attribute) { m_vertexAttributes.Append(attribute); }
			GFM_BEST_INLINE const List<VertexAttribute>& GetVertexAttributes() const noexcept { return m_vertexAttributes; }
			GFM_BEST_INLINE utils::uint32 GetVertexAttributesStride() const noexcept { return m_vertexAttributeStride;  }

			constexpr PipelineType GetType() const noexcept { return m_type; }

		protected:
			virtual void DeleteAttachedShaders() noexcept = 0;

		protected: 
			enum class ShaderIndex {
				eVERTEX_INDEX, 
				eFRAGMENT_INDEX, 
				eGEOMETRY_INDEX, 
				eTESSELATION_EVALUATION_INDEX, 
				eTESSELATION_CONTROL_INDEX, 
				eSHADER_INDEX_MAXNUM, 
				eSHADER_INDEX_NONE
			};

			static constexpr auto ShaderTypeToIndex(ShaderType type) {
				switch(type) {
				case ShaderType::eVERTEX:				  return ShaderIndex::eVERTEX_INDEX;
				case ShaderType::eFRAGMENT:				  return ShaderIndex::eFRAGMENT_INDEX;
				case ShaderType::eGEOMETRY:				  return ShaderIndex::eGEOMETRY_INDEX;
				case ShaderType::eTESSELATION_EVALUATION: return ShaderIndex::eTESSELATION_EVALUATION_INDEX;
				case ShaderType::eTESSELATION_CONTROL:    return ShaderIndex::eTESSELATION_CONTROL_INDEX;
				}
				return ShaderIndex::eSHADER_INDEX_NONE;
			}

		protected:
			List<VertexAttribute> m_vertexAttributes;
			utils::uint32 m_vertexAttributeStride = 0;
			utils::uint32 m_shaderCount = 0;
			PipelineType m_type;
			const Shader* m_AttachedShader[static_cast<utils::uint32>(ShaderIndex::eSHADER_INDEX_MAXNUM)];
	};
}//INTERNAL
}//graphic
}//gfm
#endif // PIPELINE_H