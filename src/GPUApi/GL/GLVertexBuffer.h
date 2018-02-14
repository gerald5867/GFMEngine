#pragma once
#ifndef GL_VERTEX_BUFFER_H
#define GL_VERTEX_BUFFER_H
#include "GLBuffer.h"
#include "../VertexBuffer.h"
#pragma warning(push)
#pragma warning(disable: 4250) // virtual inheritance warning ?
namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {
	class GLVertexBuffer final : public VertexBuffer, public GLBuffer<GLVertexBuffer> 
	{
	public:
		GLVertexBuffer(const GLVertexBuffer&)				= delete;
		GLVertexBuffer& operator =(const GLVertexBuffer&)   = delete;

		GLVertexBuffer(GLVertexBuffer&& )					= default;
		GLVertexBuffer& operator =(GLVertexBuffer&& )		= default;

		virtual ~GLVertexBuffer() noexcept = default;

		GLVertexBuffer(BufferUsage usage);
	
	public:

		virtual void* MapMemory(BufferAcces access) const override;
		virtual void UnmapMemory(void* bufferMemory) const override;
		virtual void Resize(utils::uint32 newSize) const override;

	protected:
		virtual void UploadRawData(const void* data, utils::uint32 size) const override;
	};

}//GL
}//gpu
}//INTERNAL
}//gfm
#pragma warning(pop) // 4250
#endif //GL_VERTEX_BUFFER_H