#pragma once
#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
#include "../DataStructures/List.h"
#include "BufferType.h"
#include "BufferUsage.h"
#include "Buffer.h"
#include "../Utils/Types.h"

namespace gfm {
namespace INTERNAL {
namespace gpu {
		class IndexBuffer : public virtual Buffer {

		public:
			virtual ~IndexBuffer() noexcept = default;
			virtual void UploadData(const utils::uint16* data, utils::uint32 count) = 0;
			virtual void UploadData(const utils::uint32* data, utils::uint32 count) = 0;
			virtual void UploadData(const List<utils::uint16>& data) = 0;
			virtual void UploadData(const List<utils::uint32>& data) = 0;

			virtual utils::uint32 Count() const noexcept = 0;

			IndexBuffer(BufferUsage usage) : Buffer(usage, BufferType::eINDEX) {}

		protected:
			utils::uint32 m_count = 0;
		};
}//INTERNAL
}//graphic
}//gfm
#endif // INDEX_BUFFER_H