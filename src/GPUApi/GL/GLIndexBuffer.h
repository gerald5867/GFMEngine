#pragma once
#include "GLBuffer.h"
#include "../IndexBuffer.h"
#ifndef GL_INDEX_BUFFER_H
#define GL_INDEX_BUFFER_H
#pragma warning(push)
#pragma warning(disable: 4250) // virtual inheritance warning ?
namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {

	class GLIndexBuffer final : public IndexBuffer, public GLBuffer<GLIndexBuffer>
	{
	public:
		GLIndexBuffer(const GLIndexBuffer&) = delete;
		GLIndexBuffer& operator =(const GLIndexBuffer&) = delete;

		GLIndexBuffer(GLIndexBuffer&&) = default;
		GLIndexBuffer& operator =(GLIndexBuffer&&) = default;

		GLIndexBuffer(BufferUsage usage);
		virtual ~GLIndexBuffer() = default;

	public:
		virtual void UploadData(const utils::uint16* data, utils::uint32 count) override;
		virtual void UploadData(const utils::uint32* data, utils::uint32 count) override;
		virtual void UploadData(const List<utils::uint16>& data) override;
		virtual void UploadData(const List<utils::uint32>& data) override;

		virtual utils::uint32 Count() const noexcept override;
	};

}//GL
}//gpu
}//INTERNAL
}//gfm
#pragma warning(pop) // 4250
#endif //GL_INDEX_BUFFER_H

