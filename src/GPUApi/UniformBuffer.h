#pragma once
#include "Buffer.h"
#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

namespace gfm {
namespace INTERNAL {
namespace gpu {
	class UniformBuffer : public virtual Buffer {
		public:
			virtual ~UniformBuffer() noexcept = default;
			UniformBuffer(BufferUsage usage): Buffer(usage, BufferType::eUNIFORM) {}
			virtual void UploadData(const void* data, utils::uint32 size) const = 0;

			virtual void* MapMemory(BufferAcces access) const = 0;
			virtual void UnmapMemory(void* bufferMemory) const = 0;
			virtual void Resize(utils::uint32 newSize) const = 0;

		public:
			virtual utils::int32 GetBindingPoint() const = 0;
			virtual utils::int32 GetMaximumUboCount() const = 0;
			virtual utils::int32 GetMaximumSize() const = 0;

	};

}//graphic
}//INTERNAL
}//gfm

#endif // UNIFORM_BUFFER_H