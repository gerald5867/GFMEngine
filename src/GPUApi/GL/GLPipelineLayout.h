#pragma once
#ifndef GL_PIPELINE_LAYOUT_H
#define GL_PIPELINE_LAYOUT_H
#include "GL.h"
#include "../VertexAttribute.h"
#include "../../Utils/Types.h"
#include "../PipelineLayout.h"
namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {

	class GLPipelineLayout final : public PipelineLayout 
	{
	public:
		virtual void CreateFromPipeline(PipelineType type) override;
		virtual void CreateFromPipeline(const Pipeline& pipeline) override;
		virtual void AppendBuffer(const Buffer& buffer) override;
		virtual void EnableVertexAttribute(const VertexAttribute& attr, utils::uint32 stride) override;
		virtual void CreateFromVertexBufferLayout(const VertexBufferLayout& layout) override;

		virtual void Bind() const noexcept override;
		virtual void Unbind() const noexcept override;

		GLPipelineLayout();
		virtual ~GLPipelineLayout() noexcept;

		static utils::uint32 GetCurrentBoundLayoutID() noexcept;
	private:

		struct RawType {
			utils::uint32 glType;
			utils::uint32 count;
			constexpr operator bool() const noexcept {
				return glType && count;
			}
		};

		constexpr static bool IsLinearType(VertexAttributeType type) {
			return type >= VertexAttributeType::eVEC2 && type <= VertexAttributeType::eMAT4;
		}

		constexpr static auto VertexAttributeTypeToGlTYPE(VertexAttributeType type) {
			switch(type) {
			case VertexAttributeType::eVEC2:  return GL_FLOAT;
			case VertexAttributeType::eVEC3:  return GL_FLOAT;
			case VertexAttributeType::eVEC4:  return GL_FLOAT;
			case VertexAttributeType::eMAT2:  return GL_FLOAT;
			case VertexAttributeType::eMAT3:  return GL_FLOAT;
			case VertexAttributeType::eMAT4:  return GL_FLOAT;
			case VertexAttributeType::eINT:   return GL_INT;
			case VertexAttributeType::eUINT:  return GL_UNSIGNED_INT;
			case VertexAttributeType::eFLOAT: return GL_FLOAT;
			case VertexAttributeType::eDOUBLE:return GL_DOUBLE;
			case VertexAttributeType::eUBYTE: return GL_UNSIGNED_BYTE;
			}
			GFM_DEBUG_BREAK;
			return 0;
		}

	private:
		mutable utils::uint32 m_id = 0;
		utils::uint32 m_attributeCount = 0;
		static utils::uint32 ms_currentBoundPipelineLayout;
	};

}//GL
}//gpu
}//INTERNAL
}//gfm
#endif // GL_PIPELINE_LAYOUT_H