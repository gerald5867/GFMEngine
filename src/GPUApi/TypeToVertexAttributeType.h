#pragma once
#include "VertexAttribute.h"
#include "../Utils/Types.h"

#ifndef VERTEX_ATTRIBUTE_TYPE_TO_TYPE_H
#define VERTEX_ATTRIBUTE_TYPE_TO_TYPE_H
namespace gfm {
namespace INTERNAL {
namespace gpu {
	//HÄTTE GENAU UMGEHKERT SEIN MÜSSEN !
	template<typename T> struct TypeToVertexAttributeType {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eNONE;
		static constexpr const utils::uint32 Count = 0;
		using DataType = void;
	};

	template<> struct TypeToVertexAttributeType<float> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eFLOAT;
		static constexpr const utils::uint32 Count = 1;
		using DataType = float;
	};

	template<> struct TypeToVertexAttributeType<bool> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eBOOL;
		static constexpr const utils::uint32 Count = 1;
		using DataType = bool;
	};

	template<> struct TypeToVertexAttributeType<double> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eDOUBLE;
		static constexpr const utils::uint32 Count = 1;
		using DataType = double;
	};

	template<> struct TypeToVertexAttributeType<utils::uint32> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eUINT;
		static constexpr const utils::uint32 Count = 1;
		using DataType = utils::uint32;
	};

	template<> struct TypeToVertexAttributeType<utils::byte> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eUBYTE;
		static constexpr const utils::uint32 Count = 1;
		using DataType = utils::byte;
	};

	template<> struct TypeToVertexAttributeType<utils::int32> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eINT;
		static constexpr const utils::uint32 Count = 1;
		using DataType = utils::int32;
	};

	template<> struct TypeToVertexAttributeType<math::Vec2> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eFLOAT;
		static constexpr const utils::uint32 Count = 2;
		using DataType = float;
	};

	template<> struct TypeToVertexAttributeType<math::Vec3> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eFLOAT;
		static constexpr const utils::uint32 Count = 3;
		using DataType = float;
	};

	template<> struct TypeToVertexAttributeType<math::Vec4> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eFLOAT;
		static constexpr const utils::uint32 Count = 4;
		using DataType = float;
	};

	template<> struct TypeToVertexAttributeType<math::Mat2> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eFLOAT;
		static constexpr const utils::uint32 Count = 4;
		using DataType = float;
	};

	template<> struct TypeToVertexAttributeType<math::Mat3> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eFLOAT;
		static constexpr const utils::uint32 Count = 9;
		using DataType = float;
	};

	template<> struct TypeToVertexAttributeType<math::Mat4> {
		static constexpr const VertexAttributeType Type = VertexAttributeType::eFLOAT;
		static constexpr const utils::uint32 Count = 16;
		using DataType = float;
	};

}//gpu
}//INTERNAL
}//gfm
#endif // VERTEX_ATTRIBUTE_TYPE_TO_TYPE_H