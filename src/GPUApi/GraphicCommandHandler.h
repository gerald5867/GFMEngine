#pragma once
#include "../Utils/Types.h"
#include "GraphicAPI.h"
#include "GL/GL.h"
#ifndef GRAPHIC_COMMAND_HANDLER_H
#define GRAPHIC_COMMAND_HANDLER_H
namespace gfm {
namespace INTERNAL {
namespace gpu {

	enum class DrawMode {
		ePOINTS,
		eLINES,
		eLINE_LOOP,
		eLINE_STRIP,
		eTRIANGLES,
		eTRIANGLE_STRIP,
		eTRIANGLE_FAN,
	};

	enum class DrawIndexedType {
		eUBYTE = 0x1401, eUSHORT = 0x1403, eUINT = 0x1405
	};
	
	enum class ClearTarget {
		eCOLOR_BUFFER_BIT = (1 << 14),
		eDEPTH_BUFFER_BIT = (1 << 8),
		eACCUM_BUFFER_BIT = (1 << 9),
		eSTENCIL_BUFFER_BIT = (1 << 10)
	};

	class GraphicCommandHandler 
	{
	public:
		static GraphicCommandHandler& Initialize(GraphicAPI api);
		static GraphicCommandHandler& Instance();
		static void Destroy() noexcept;

	public:
		virtual void DrawInstancedIndexed(DrawMode mode, utils::uint32 elementCount, DrawIndexedType type, utils::uint32 instanceCount, const void * indices = nullptr) const = 0;
		virtual void DrawIndexed(DrawMode mode, utils::uint32 elementCount, DrawIndexedType type, const void* indices = nullptr) const = 0;
		virtual void Clear(ClearTarget targets) const = 0;
		virtual void UpdateViewport(utils::uint32 width, utils::uint32 height) const = 0;
		virtual void UpdateViewport(utils::uint32 x, utils::uint32 y, utils::uint32 width, utils::uint32 height) const = 0;

		virtual ~GraphicCommandHandler() noexcept = default;

	protected:
		GraphicCommandHandler() = default;

	private:
		GraphicAPI m_api = GraphicAPI::eNONE;
		static GraphicCommandHandler* mp_instance;
	};

}//gpu
}//INTERNAL
}//gfm
#endif //GRAPHIC_COMMAND_HANDLER_H