#pragma once
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include "BufferType.h"
#include "BufferUsage.h"
#include "Buffer.h"
#include "../Utils/Types.h"
#include "../DataStructures/List.h"
#include "../DataStructures/Array.h"

namespace gfm {
namespace INTERNAL {
namespace gpu {
	

//TODO ABSTRACT THE UPLOAD METHODS IN THE CLASS SO THE BUFFERS THAT NEED IT CAN INHERT IT
	class VertexBuffer : public virtual Buffer {
		public:
			virtual ~VertexBuffer() noexcept = default;
			VertexBuffer(BufferUsage usage): Buffer(usage, BufferType::eVERTEX) {}

			virtual void* MapMemory(BufferAcces access) const = 0;
			virtual void UnmapMemory(void* bufferMemory) const = 0;
			virtual void Resize(utils::uint32 newSize) const = 0;
		
		public:
			template<typename T>
			void UploadData(const T* data, utils::uint32 count) {
				UploadRawData(reinterpret_cast<const void*>(data), count * sizeof(T));
			}

			template<typename T>
			void UploadData(const List<T>& data) {
				UploadRawData(reinterpret_cast<const void*>(data.Raw()), data.Length() * sizeof(T));
			}

			template<typename T, utils::uint32 ArrayLen>
			void UploadData(const Array<T, ArrayLen>& data) {
				UploadRawData(reinterpret_cast<const void*>(data.Raw()), data.Length() * sizeof(T));
			}

		protected:
			virtual void UploadRawData(const void* data, utils::uint32 size) const = 0;
	};
}//INTERNAL
}//graphic
}//gfm
#endif // VERTEX_BUFFER_H