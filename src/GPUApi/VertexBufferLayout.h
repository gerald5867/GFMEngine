#pragma once
#include "TypeToVertexAttributeType.h"
#include "..\DataStructures\List.h"

#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H
namespace gfm {
namespace INTERNAL {
namespace gpu {

	class VertexBufferLayout {

		public:

			template<typename T>
			void PushAttribute(utils::uint32 count, bool normalized) {
				VertexAttribute attribute;
				attribute.pipelineType = PipelineType::eNONE;
				attribute.type = TypeToVertexAttributeType<T>::Type;
				attribute.locationIndex = m_lastLocationIndex++;
				attribute.componentOffset = m_stride;
				attribute.normalized = normalized;
				auto realCount = count * TypeToVertexAttributeType<T>::Count;
				attribute.componentCount = realCount;
				typedef typename TypeToVertexAttributeType<T>::DataType Type;
				m_stride += sizeof(Type) * realCount;
				m_attributes.Append(attribute);
			}

			GFM_BEST_INLINE utils::uint32 GetStride() const noexcept {
				return m_stride;
			}

			GFM_BEST_INLINE utils::uint32 GetLastLocation() const noexcept {
				return m_lastLocationIndex;
			}
	
			GFM_BEST_INLINE const List<VertexAttribute>& GetAttributes() const noexcept {
				return m_attributes;
			}

		private:
			utils::uint32 m_stride = 0;
			utils::uint32 m_lastLocationIndex = 0;
			List<VertexAttribute> m_attributes;
	};
}//gpu

}//INTERNAL
}//gfm
#endif // VERTEX_BUFFER_LAYOUT_H