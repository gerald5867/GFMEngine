#pragma once
#include "..\GraphicCommandHandler.h"
#ifndef GL_GRAPHIC_COMMAND_HANDLER_H
#define GL_GRAPHIC_COMMAND_HANDLER_H
namespace gfm {
namespace INTERNAL {
namespace gpu {
namespace GL {

	class GLGraphicCommandHandler final : public GraphicCommandHandler
	{
	public:
		GLGraphicCommandHandler() = default;
		virtual ~GLGraphicCommandHandler() noexcept = default;

	public:
		virtual void DrawInstancedIndexed(DrawMode mode, utils::uint32 elementCount, DrawIndexedType type, utils::uint32 instanceCount, const void* indices = nullptr) const override;
		virtual void DrawIndexed(DrawMode mode, utils::uint32 elementCount, DrawIndexedType type, const void* indices = nullptr) const override;
		virtual void Clear(ClearTarget targets) const override;

		virtual void UpdateViewport(utils::uint32 width, utils::uint32 height) const override;
		virtual void UpdateViewport(utils::uint32 x, utils::uint32 y, utils::uint32 width, utils::uint32 height) const override;

		
	};

}//GL
}//gpu
}//INTERNAL
}//gfm
#endif // GL_GRAPHIC_COMMAND_HANDLER_H