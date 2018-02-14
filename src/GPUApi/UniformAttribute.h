#pragma once
#ifndef UNIFORM_ATTRIBUTE_H
#define UNIFORM_ATTRIBUTE_H
#include "../Macro/Assertions.h"
#include "../Utils/Types.h"
#include "../DataStructures/String.h"
#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "PipelineType.h"
#include "ShaderType.h"

namespace gfm {
namespace INTERNAL {
namespace gpu {

enum class UniformAttributeType {
	eNONE, eCHAR, eUCHAR, eINT, eUINT, eFLOAT, eDOUBLE, eVEC2, eVEC3, eVEC4, eMAT2, eMAT3, eMAT4
};

	struct UniformAttribute
	{
		PipelineType		 m_pipelineType  = PipelineType::eNONE;
		UniformAttributeType m_type		     = UniformAttributeType::eNONE;
		ShaderType			 m_shaderType    = ShaderType::eSHADER_NONE;
		utils::uint32	     m_locationIndex = 0;
	
		constexpr auto UniformAttributeTypeToSize(UniformAttributeType type) noexcept {
			switch(type) {
			case UniformAttributeType::eCHAR: return sizeof(utils::int8);
			case UniformAttributeType::eUCHAR: return sizeof(utils::uint8);
			case UniformAttributeType::eINT: return sizeof(utils::int32);
			case UniformAttributeType::eUINT: return sizeof(utils::uint32);
			case UniformAttributeType::eFLOAT: return sizeof(float);
			case UniformAttributeType::eDOUBLE: return sizeof(double);
			case UniformAttributeType::eVEC2: return sizeof(math::Vec2);
			case UniformAttributeType::eVEC3: return sizeof(math::Vec3);
			case UniformAttributeType::eVEC4: return sizeof(math::Vec4);
			case UniformAttributeType::eMAT2: return sizeof(math::Mat2);
			case UniformAttributeType::eMAT3: return sizeof(math::Mat3);
			case UniformAttributeType::eMAT4: return sizeof(math::Mat4);
			}
			GFM_DEBUG_BREAK;
		}
	};

}//gpu
}//INTERNAL
}//gfm
#endif // UNIFORM_ATTRIBUTE_H