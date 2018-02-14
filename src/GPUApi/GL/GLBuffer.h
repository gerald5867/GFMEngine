#pragma once
#ifndef GL_BUFFER_H
#define GL_BUFFER_H
#include <atomic>
#include "../../Utils/Types.h"
#include "GL.h"
#include "../Buffer.h"
#include "../BufferType.h"
#include "../BufferUsage.h"

namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {

	class GLVertexBuffer;
	class GLIndexBuffer;
	class GLUniformBuffer;

	template<typename DerivedType> // CRTP FOR ms_currentBoundBuffer
	class GLBuffer : public virtual Buffer  
	{
		friend class GLPipeline;
	protected:
		GLBuffer(const GLBuffer&)			  = delete;
		GLBuffer& operator =(const GLBuffer&) = delete;
		GLBuffer(GLBuffer&& other);
		GLBuffer& operator =(GLBuffer&& other);

		virtual ~GLBuffer() noexcept;
		GLBuffer(BufferUsage usage, BufferType type);

	public:
		virtual void Bind() const noexcept override;
		virtual void Unbind() const noexcept override;
		virtual bool IsBound() const noexcept override;

	protected:
		virtual void Create() const noexcept override;
		virtual void Destroy() const noexcept override;

	protected:
		mutable utils::uint32 m_id = 0;

	private:
		volatile static std::atomic<utils::uint32> ms_currentBoundBuffer;
	};

}//GL
}//gpu
}//INTERNAL
}//gfm
#endif //GL_BUFFER_H