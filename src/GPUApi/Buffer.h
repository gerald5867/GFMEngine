#pragma once
#ifndef BUFFER_H
#define BUFFER_H
#include "BufferType.h"
#include "BufferUsage.h"
#include "../Utils/Types.h"

enum class BufferAcces {
	eREAD = 35000, eWRITE = 35001, eREAD_WRITE = 35002
};

namespace gfm {
namespace INTERNAL {
namespace gpu {

	class Buffer {
	protected:
		virtual ~Buffer() noexcept = default;
		Buffer(BufferUsage usage, BufferType type);
		Buffer(Buffer&&)					= default;
		Buffer(const Buffer&)				= default;
		Buffer& operator =(Buffer&&)	    = default;
		Buffer& operator =(const Buffer&) = default;

	public:
		virtual void Bind() const noexcept = 0;
		virtual void Unbind() const noexcept = 0;
		virtual bool IsBound() const noexcept = 0;

	protected:
		virtual void Create() const noexcept = 0;
		virtual void Destroy() const noexcept = 0;
		
	protected:
		BufferUsage GetUsage() const noexcept;
		BufferType GetType() const noexcept;

	protected:
		BufferUsage m_usage;
		BufferType m_type;

	};
}//INTERNAL
}//graphic
}//gfm
#endif //BUFFER_H