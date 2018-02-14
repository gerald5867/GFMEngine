#include "Circle.h"
#include "CircleRenderer.h"
#include "../Math/Constants.h"
#include "../GPUApi/VertexBuffer.h"
#include "../GPUApi/IndexBuffer.h"
#include "../GPUApi/UniformBuffer.h"
#include "../GPUApi/PipelineLayout.h"
#include "../GPUApi/GraphicObjectFactory.h"
#include "../GPUApi/PipelineManager.h"
#include "../GPUApi/GraphicCommandHandler.h"
#include <iostream>
#include "../Math/Vector2D.h"


gfm::graphic::CircleRenderer::CircleRenderer()
: IRenderer2D(600, 600, gfm::math::Matrix4x4::Orthographic(0.0f, 600.0f, 600.0f, 0.0f))
, m_CircleDrawCount(0) {
	using namespace INTERNAL::gpu; // for GraphicObjectFactory BufferUsage, Pipeline
	m_pipelineLayout = GraphicObjectFactory::instance().CreatePipelineLayout();
	m_indexBuffer = GraphicObjectFactory::instance().CreateIndexBuffer(BufferUsage::eSTATIC_DRAW);
	m_vertexBuffer = GraphicObjectFactory::instance().CreateVertexBuffer(BufferUsage::eSTATIC_DRAW);
	m_uniformBuffer = GraphicObjectFactory::instance().CreateUniformBuffer(BufferUsage::eDYNAMIC_DRAW);
	m_pipelineLayout->Bind();
	m_vertexBuffer->Bind();
	m_pipelineLayout->AppendBuffer(*m_vertexBuffer);
	m_uniformBuffer->Resize(s_UINFORMBUFFERMAXSIZE);
	CreateVertexBufferLayout();
	FillIndexBuffer();
	FillVertexBuffer();
	m_freeCircleIndices.Reserve(s_CIRCLEMAXCOUNT);
	for(utils::int32 i = s_CIRCLEMAXCOUNT - 1; i >= 0; --i) {
		m_freeCircleIndices.Append(i);
	}
}

gfm::graphic::CircleRenderer::~CircleRenderer() noexcept {
}

void gfm::graphic::CircleRenderer::FillIndexBuffer() {
	static List<utils::uint16> indices;
	if (indices.Empty())
	{
		indices.Reserve(s_CIRCLEVERTEXPRECISION * 3);
		for (auto i = 1; i < s_CIRCLEVERTEXPRECISION - 1; i++) {
			indices.Append(0);
			indices.Append(i);
			indices.Append(i + 1);
		}
	}
	m_indexBuffer->UploadData(indices);
}

void gfm::graphic::CircleRenderer::FillVertexBuffer() {
	static Array<CircleVertexData, s_CIRCLEVERTEXPRECISION> vertices;
	static bool verticesFilled = false;
	if (!verticesFilled)
	{
		for (auto i = 0U; i < s_CIRCLEVERTEXPRECISION; ++i) {
			auto& curVertex = vertices[i];
			curVertex.vertex.x = std::cos(static_cast<float>(i) / static_cast<float>(s_CIRCLEVERTEXPRECISION) * 2.0f * math::PI);
			curVertex.vertex.y = std::sin(static_cast<float>(i) / static_cast<float>(s_CIRCLEVERTEXPRECISION) * 2.0f * math::PI);
			curVertex.textureCoordiantes = { 0.0f , 0.0f }; // TODO: TEXTURE COORDS!
		}
		verticesFilled = true;
	}
	m_vertexBuffer->UploadData(vertices);
}

void gfm::graphic::CircleRenderer::CreateVertexBufferLayout() {
	m_vertexBufferLayout.PushAttribute<math::Vec2>(1, false);
	m_vertexBufferLayout.PushAttribute<math::Vec2>(1, false);
	m_pipelineLayout->CreateFromVertexBufferLayout(m_vertexBufferLayout);
}

void gfm::graphic::CircleRenderer::Update() {
	m_pipelineLayout->Bind();
	m_CircleDrawCount = s_CIRCLEMAXCOUNT - m_freeCircleIndices.Length();
	if (m_toRemoveCircels.Empty() && m_toUpdateCircels.Empty()) {
		return;
	}
	CircleUniformData* uboData = reinterpret_cast<CircleUniformData*>(m_uniformBuffer->MapMemory(BufferAcces::eWRITE));
	while (!m_toRemoveCircels.Empty()) {
		utils::uint32 circleIndex = m_toRemoveCircels.PopLast();
		utils::uint32 moveSize = s_UINFORMBUFFERMAXSIZE - (circleIndex + 2) * sizeof(CircleUniformData);
		std::memmove(uboData + circleIndex, uboData + circleIndex + 1, moveSize);
	}
	math::Vec2 windowSize{static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight)};
	while (!m_toUpdateCircels.Empty()) {
		const Circle* circle = m_toUpdateCircels.PopLast();
		if (circle == nullptr) {
			continue;
		}
		if (!circle->IsShow()) {
			--m_CircleDrawCount;
			std::memset(&uboData[circle->m_rendererIndex], 0, sizeof(CircleUniformData));
			continue;
		}
		math::Vec2 finalCirclePosition = circle->GetPosition() * 2.0f - (windowSize / 2) + circle->m_radius;
		uboData[circle->m_rendererIndex] = {circle->GetColor(), finalCirclePosition, circle->m_radius * 2.0f / m_windowWidth * 2.0f, circle->m_scale};
	}
	m_uniformBuffer->UnmapMemory(uboData);
 }

void gfm::graphic::CircleRenderer::Render() {
	m_pipelineLayout->Bind();
	using namespace INTERNAL::gpu; // for PipelineManager
	auto& pipe = PipelineManager::instance().GetPipeline(PipelineType::eCIRCLE2D);
	pipe.Bind();
	m_indexBuffer->Bind();
	m_uniformBuffer->Bind();
	pipe.PushUniform(m_projectionMatrix, s_PROJECTIONMATRIXNAME);
	const auto& ubo = *m_uniformBuffer;
	pipe.BindUniformBuffer(ubo, s_UNIFORMBLOCKNAME);
	GraphicCommandHandler::Instance().DrawInstancedIndexed(
		DrawMode::eTRIANGLES, m_indexBuffer->Count(), DrawIndexedType::eUSHORT, m_CircleDrawCount);
	pipe.Unbind();
	m_indexBuffer->Unbind();
	m_pipelineLayout->Unbind();
	m_uniformBuffer->Unbind();
 }

gfm::utils::uint32 gfm::graphic::CircleRenderer::Submit(const Circle& circle) {
	auto circleIndex = m_freeCircleIndices.PopLast();
	m_toUpdateCircels.Append(&circle);
	circle.m_updateListIndex = m_toUpdateCircels.Length() - 1;
	return circleIndex;
}

void gfm::graphic::CircleRenderer::Remove(const Circle& circle) {
	m_freeCircleIndices.Append(circle.m_rendererIndex);
	if(circle.m_updateListIndex < m_toUpdateCircels.Length()) {
		m_toUpdateCircels[circle.m_updateListIndex] = nullptr;
	}
}

void gfm::graphic::CircleRenderer::NeedUpdate(const Circle& circle) {
	m_toUpdateCircels.Append(&circle);
}