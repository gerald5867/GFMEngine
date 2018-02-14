#include "Rectangle.h"
#include "../GPUApi/VertexBuffer.h"
#include "../GPUApi/IndexBuffer.h"
#include "../GPUApi/PipelineLayout.h"
#include "../GPUApi/GraphicObjectFactory.h"
#include "../GPUApi/PipelineManager.h"
#include "../GPUApi/GraphicCommandHandler.h"
#include <iostream>
#include "../Math/Convertions.h"
#include "RectangleRenderer.h"

void gfm::graphic::RectangleRenderer::Update() {
	m_pipelineLayout->Bind();
	m_rectangleDrawCount = s_RECTANGLEMAXCOUNT - m_freeRectangleIndices.Length();
	if(m_toUpdateRectangles.Empty() && m_toRemoveRectangles.Empty()) {
		return;
	}
	RectangleVertexData* gpuData = reinterpret_cast<RectangleVertexData*>(m_vertexBuffer->MapMemory(BufferAcces::eWRITE));
	while(!m_toRemoveRectangles.Empty()) {
		utils::uint32 angleIndex = m_toRemoveRectangles.PopLast();
		utils::uint32 moveSize = s_RECTANGLEVERTEXBUFFERSIZE - (angleIndex + 2) * s_RECTANGLESIZE;
		std::memmove(gpuData + angleIndex, gpuData + angleIndex + 1, moveSize);
	}
	while(!m_toUpdateRectangles.Empty()) {
		const Rectangle* angle = m_toUpdateRectangles.PopLast();
		if(angle == nullptr) {
			continue;
		}
		if(!angle->IsShow()) {
			--m_rectangleDrawCount;
			std::memset(&gpuData[(angle->m_rendererIndex * 4) + 0], 0, s_RECTANGLESIZE);
			continue;
		}
		using uint32 = utils::uint32;
		math::Vec4 color = angle->GetColor();
		auto r = static_cast<uint32>(color.x * 255.0f);
		auto g = static_cast<uint32>(color.y * 255.0f);
		auto b = static_cast<uint32>(color.z * 255.0f);
		auto a = static_cast<uint32>(color.w * 255.0f);
		auto resultColor = a << 24 | b << 16 | g << 8 | r;
		gpuData[(angle->m_rendererIndex * 4) + 0] = {angle->LefTop(), resultColor };
		gpuData[(angle->m_rendererIndex * 4) + 1] = {angle->RightTop(), resultColor };
		gpuData[(angle->m_rendererIndex * 4) + 2] = {angle->RightBottom(), resultColor };
		gpuData[(angle->m_rendererIndex * 4) + 3] = {angle->LeftBottom(), resultColor };
	}
	m_vertexBuffer->UnmapMemory(gpuData);
}

void gfm::graphic::RectangleRenderer::Render() {
	m_pipelineLayout->Bind();
	using namespace INTERNAL::gpu; // for PipelineManager
	auto& pipe = PipelineManager::instance().GetPipeline(PipelineType::eRECTANGLE2D);
	pipe.Bind();
	m_indexBuffer->Bind();
	pipe.PushUniform(m_projectionMatrix, s_PROJECTIONMATRIXNAME);
	GraphicCommandHandler::Instance().DrawIndexed(DrawMode::eTRIANGLES, m_rectangleDrawCount * 6, DrawIndexedType::eUSHORT);
	pipe.Unbind();
	m_indexBuffer->Unbind();
	m_pipelineLayout->Unbind();
}

gfm::utils::uint32 gfm::graphic::RectangleRenderer::Submit(const Rectangle& rectanlge) {
	auto circleIndex = m_freeRectangleIndices.PopLast();
	m_toUpdateRectangles.Append(&rectanlge);
	rectanlge.m_updateListIndex = m_toUpdateRectangles.Length() - 1;
	return circleIndex;
}

void gfm::graphic::RectangleRenderer::Remove(const Rectangle& rectangle) {
	m_toRemoveRectangles.Append(rectangle.m_rendererIndex);
	if(rectangle.m_updateListIndex < m_toUpdateRectangles.Length()) {
		m_toUpdateRectangles[rectangle.m_updateListIndex] = nullptr;
	}
}

void gfm::graphic::RectangleRenderer::NeedUpdate(const Rectangle& rectangle) {
	m_toUpdateRectangles.Append(&rectangle);
}

gfm::graphic::RectangleRenderer::RectangleRenderer()
: IRenderer2D(600, 600, gfm::math::Matrix4x4::Orthographic(0.0f, 600, 600, 0.0f)) // for now
, m_rectangleDrawCount(0) {
	using namespace INTERNAL::gpu; // for GraphicObjectFactory BufferUsage, Pipeline
	m_indexBuffer = GraphicObjectFactory::instance().CreateIndexBuffer(BufferUsage::eSTATIC_DRAW);
	m_pipelineLayout = GraphicObjectFactory::instance().CreatePipelineLayout();
	m_vertexBuffer = GraphicObjectFactory::instance().CreateVertexBuffer(BufferUsage::eDYNAMIC_DRAW);
	m_pipelineLayout->Bind();
	m_vertexBuffer->Bind();
	m_pipelineLayout->AppendBuffer(*m_vertexBuffer);
	m_vertexBuffer->Resize(s_RECTANGLEVERTEXBUFFERSIZE);
	CreateVertexBufferLayout();
	m_pipelineLayout->CreateFromVertexBufferLayout(m_vertexBufferLayout);
	FillIndexBuffer();
	m_freeRectangleIndices.Reserve(s_RECTANGLEMAXCOUNT);
	for(utils::int32 i = s_RECTANGLEMAXCOUNT - 1; i >= 0; --i) {
		m_freeRectangleIndices.Append(i);
	}
}

gfm::graphic::RectangleRenderer::~RectangleRenderer() noexcept {
	m_pipelineLayout->Bind();
	using namespace INTERNAL::gpu; // for PipelineManager
	auto& pipe = PipelineManager::instance().GetPipeline(PipelineType::eCIRCLE2D);
	pipe.Bind();
	m_indexBuffer->Bind();
	pipe.PushUniform(m_projectionMatrix, s_PROJECTIONMATRIXNAME);
	GraphicCommandHandler::Instance().DrawIndexed(DrawMode::eTRIANGLES, m_rectangleDrawCount * 6, DrawIndexedType::eUSHORT);
	pipe.Unbind();
	m_indexBuffer->Unbind();
	m_pipelineLayout->Unbind();
}

void gfm::graphic::RectangleRenderer::FillIndexBuffer() const {
	List<utils::uint16> indices(s_RECTANGLEINDEXBUFFERLENGTH); // should be dynamic array
	auto offset = 0U;
	for(auto i = 0U; i < s_RECTANGLEINDEXBUFFERLENGTH;) {
		indices[i++] = offset;
		indices[i++] = offset + 1;
		indices[i++] = offset + 2;
		indices[i++] = offset + 2;
		indices[i++] = offset + 3;
		indices[i++] = offset;
		offset += 4;
	}
	m_indexBuffer->Bind();
	m_indexBuffer->UploadData(indices.Raw(), s_RECTANGLEINDEXBUFFERLENGTH);
}

void gfm::graphic::RectangleRenderer::CreateVertexBufferLayout() {
	m_vertexBufferLayout.PushAttribute<math::Vec2>(1, false);
	m_vertexBufferLayout.PushAttribute<utils::byte>(4, true);
}

