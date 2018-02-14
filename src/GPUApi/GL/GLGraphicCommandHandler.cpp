#pragma once
#include "GL.h"
#include "../../Macro/Assertions.h"
#include "GLGraphicCommandHandler.h"

void gfm::INTERNAL::gpu::GL::GLGraphicCommandHandler::DrawInstancedIndexed(DrawMode mode, utils::uint32 elementCount, DrawIndexedType type, utils::uint32 instanceCount, const void * indices) const {
	ASSERT_GL(glDrawElementsInstanced(static_cast<utils::uint32>(mode), elementCount, static_cast<utils::uint32>(type), indices, instanceCount));
}

void gfm::INTERNAL::gpu::GL::GLGraphicCommandHandler::DrawIndexed(
	DrawMode mode, utils::uint32 elementCount, DrawIndexedType type, const void* indices /*= nullptr*/) const {
	ASSERT_GL(glDrawElements(static_cast<utils::uint32>(mode), elementCount, static_cast<utils::uint32>(type), indices));
}

void gfm::INTERNAL::gpu::GL::GLGraphicCommandHandler::Clear(ClearTarget targets) const {
	ASSERT_GL(glClear(static_cast<utils::uint32>(targets)));
}

void gfm::INTERNAL::gpu::GL::GLGraphicCommandHandler::UpdateViewport(utils::uint32 width, utils::uint32 height) const {
	ASSERT_GL(glViewport(0, 0, width, height));
}

void gfm::INTERNAL::gpu::GL::GLGraphicCommandHandler::UpdateViewport(utils::uint32 x, utils::uint32 y, utils::uint32 width, utils::uint32 height) const {
	ASSERT_GL(glViewport(x, y, width, height));
}

