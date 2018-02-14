#pragma once
#include "GLBuffer.h"
#include "../UniformBuffer.h"
#ifndef GL_UNIFORM_BUFFER_H
#define GL_UNIFORM_BUFFER_H
#pragma warning(push)
#pragma warning(disable: 4250) // virtual inheritance warning ?
namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {

class GLUniformBuffer final : public UniformBuffer, public GLBuffer<GLUniformBuffer>
{
	public:
		GLUniformBuffer(const GLUniformBuffer&)				= delete;
		GLUniformBuffer& operator =(const GLUniformBuffer&) = delete;
		GLUniformBuffer(GLUniformBuffer&&)			   = default;
		GLUniformBuffer& operator =(GLUniformBuffer&&) = default;

		GLUniformBuffer(BufferUsage usage);
		virtual ~GLUniformBuffer() = default;

	public:

		virtual void UploadData(const void* data, utils::uint32 size) const override;
		virtual void* MapMemory(BufferAcces access) const override;
		virtual void UnmapMemory(void* bufferMemory) const override;
		virtual void Resize(utils::uint32 newSize) const override;
		
		virtual utils::int32 GetBindingPoint() const override;
		virtual utils::int32 GetMaximumUboCount() const override;
		virtual utils::int32 GetMaximumSize() const override;

	private:
		utils::int32 m_bindingPoint;

	private:
		static utils::int32 s_lastBindingPoint;
		static utils::int32 s_maxBindingCount;
		static utils::int32 s_maxSize;
};

}//GL
}//gpu
}//INTERNAL
}//gfm
#pragma warning(pop) // 4250
#endif //GL_UNIFORM_BUFFER_H

