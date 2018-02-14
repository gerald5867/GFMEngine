#pragma once
#ifndef SHADER_SOURCE_H
#define SHADER_SOURCE_H
#include "../../../DataStructures/Array.h"
#include "../../UniformAttribute.h"
#include "../../VertexAttribute.h"
#include "../../../Utils/Types.h"

namespace gfm {
namespace INTERNAL {
namespace gpu {
	class PipelineManager;
	class GLPipeline;

namespace GL {
	
	class ShaderSource
	{
		friend class PipelineManager;
		friend class GLPipeline;

		static constexpr const char vertexShader2DPrimitive[] =
			#include "RectangleShader2D.vert"
		static constexpr const char fragmentShader2DPrimitive[] = 
			#include "RectangleShader2D.frag"
		static constexpr const char vertexShader2DCircle[] =
			#include "CircleShader2D.vert"
		static constexpr const char fragmentShader2DCircle[] =
			#include "CircleShader2D.frag"

		static constexpr const char* ShaderCode[] = {
			vertexShader2DPrimitive, fragmentShader2DPrimitive,
			vertexShader2DCircle,    fragmentShader2DCircle
		};

		static constexpr const utils::uint32 ShaderLength[] = {
			sizeof(vertexShader2DPrimitive), sizeof(fragmentShader2DPrimitive),
			sizeof(vertexShader2DCircle), sizeof(fragmentShader2DCircle)
		};

		static constexpr const utils::uint32 VertexShaderIndex[static_cast<utils::uint32>(PipelineType::eMAX_NUM)] = {
			0
		};

	};
}//GL
}//gpu
}//INTERNAL
}//gfm
#endif // SHADER_SOURCE_H