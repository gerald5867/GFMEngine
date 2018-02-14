#pragma once
#include "../Macro/Assertions.h"
#include "../Utils/Types.h"
#include "../DataStructures/String.h"
#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "PipelineType.h"
#include "../Utils/Logger.h"

#ifndef VERTEX_ATTRIBUTE_H
#define VERTEX_ATTRIBUTE_H
namespace gfm {
namespace INTERNAL {
namespace gpu {

	enum class VertexAttributeType {
		eBOOL, eINT, eUINT, eFLOAT, eDOUBLE, eVEC2, eVEC3, eVEC4, eMAT2, eMAT3, eMAT4, eUBYTE, eNONE, eSTART_NUM = eBOOL, eMAX_NUM = eUBYTE
	};

	struct VertexAttribute 
	{
		PipelineType  pipelineType = PipelineType::eNONE;
		VertexAttributeType type = VertexAttributeType::eNONE;
		utils::uint32 locationIndex = 0;
		utils::uint32 componentOffset = 0;
		utils::uint32 componentCount = 0;
		bool normalized = false;

		VertexAttribute(PipelineType pipeType, VertexAttributeType attrType, utils::uint32 location,
			utils::uint32 offset, utils::uint32 compCount, bool normalize):
			pipelineType(pipeType), type(attrType), locationIndex(location), 
			componentOffset(offset), componentCount(compCount), normalized(normalize) {
		}

		VertexAttribute() = default;

		constexpr bool IsMatrix() const noexcept {
			return type == VertexAttributeType::eMAT2 || type == VertexAttributeType::eMAT3 || type == VertexAttributeType::eMAT4;
		}

		constexpr bool IsVector() const noexcept {
			return type == VertexAttributeType::eVEC2 || type == VertexAttributeType::eVEC3 || type == VertexAttributeType::eVEC4;
		}

		static constexpr auto VertexAttributeTypeToSize(VertexAttributeType type) noexcept {
			switch(type) {
			case VertexAttributeType::eBOOL: return sizeof(bool);
			case VertexAttributeType::eUBYTE: return sizeof(utils::uint8);
			case VertexAttributeType::eINT: return sizeof(utils::int32);
			case VertexAttributeType::eUINT: return sizeof(utils::uint32);
			case VertexAttributeType::eFLOAT: return sizeof(float);
			case VertexAttributeType::eDOUBLE: return sizeof(double);
			case VertexAttributeType::eVEC2: return sizeof(math::Vec2);
			case VertexAttributeType::eVEC3: return sizeof(math::Vec3);
			case VertexAttributeType::eVEC4: return sizeof(math::Vec4);
			case VertexAttributeType::eMAT2: return sizeof(math::Mat2);
			case VertexAttributeType::eMAT3: return sizeof(math::Mat3);
			case VertexAttributeType::eMAT4: return sizeof(math::Mat4);
			}
			GFM_DEBUG_BREAK;
			return 0U;
		}
	};

}//gpu
}//INTERNAL
}//gfm
#endif // VERTEX_ATTRIBUTE_H