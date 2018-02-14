#include "GLPipeline.h"
#include "GLShader.h"
#include "../../Macro/Assertions.h"
#include "../Shader.h"
#include "Shader/ShaderSource.h"
#include "../../DataStructures/detail/String/CStringHelper.h"
#include "../../TypeTraits/ArrayFunc.h"
#include <iostream>
#include "GLUniformBuffer.h"
gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLPipeline::ms_currentBoundPipeline = 0;

gfm::INTERNAL::gpu::GL::GLPipeline::~GLPipeline() noexcept {
	Destroy();
}

gfm::INTERNAL::gpu::GL::GLPipeline::GLPipeline(PipelineType type):
	Pipeline(type) {
	CreateProgram();
}

void gfm::INTERNAL::gpu::GL::GLPipeline::Create() {
	CheckReadyToCompile();
	ParseVertexAttributes();
	ASSERT_GL(glLinkProgram(m_id));
	ASSERT_GL(glValidateProgram(m_id));
	CheckLinkingSuccessfull();
}

void gfm::INTERNAL::gpu::GL::GLPipeline::Destroy() {
	ASSERT_GL(glDeleteProgram(m_id));
}

void gfm::INTERNAL::gpu::GL::GLPipeline::Bind() const noexcept {
	if(ms_currentBoundPipeline != m_id) {
		ms_currentBoundPipeline = m_id;
		ASSERT_GL(glUseProgram(m_id));
	}
}

void gfm::INTERNAL::gpu::GL::GLPipeline::Unbind() const noexcept {
	if(ms_currentBoundPipeline != 0) {
		ms_currentBoundPipeline = 0;
		ASSERT_GL(glUseProgram(0));
	}
}

void gfm::INTERNAL::gpu::GL::GLPipeline::AttachShader(const Shader* shader) {
	GFM_DEBUG_ASSERT(m_shaderCount < static_cast<utils::uint32>(ShaderIndex::eSHADER_INDEX_MAXNUM), GFM_STRING("Pipeline Max shader count was reached!"));
	GFM_DEBUG_ASSERT(shader != nullptr, GFM_STRING("nullptr as shader are not allowed!"));
	ASSERT_GL(glAttachShader(m_id, dynamic_cast<const GLShader*>(shader)->GetID()));
	m_AttachedShader[m_shaderCount++] = shader;
}

void gfm::INTERNAL::gpu::GL::GLPipeline::PushUniform(const math::Matrix4x4 & mat, const char * name) const {
	//TODO: MAKE DICTIONARY AND SAFE THE IDS !!
	auto loc = glGetUniformLocation(m_id, name);
	GFM_DEBUG_ASSERT(loc != -1, GFM_STRING(""));
	ASSERT_GL(glUniformMatrix4fv(loc, 1, GL_FALSE, mat.elements));
}

void gfm::INTERNAL::gpu::GL::GLPipeline::CheckReadyToCompile() {
	auto hasFragment = false;
	auto hasVertex = false;
	for(auto i = 0U; i < static_cast<utils::uint32>(ShaderIndex::eSHADER_INDEX_MAXNUM); ++i) {
		if(m_AttachedShader[i] != nullptr) {
			auto stype = m_AttachedShader[i]->GetType();
			if(stype == ShaderType::eFRAGMENT) {
				hasFragment = true;
			}
			if(stype == ShaderType::eVERTEX) {
				hasVertex = true;
			}
			if(!m_AttachedShader[i]->IsCompiled()) {
				GFM_LOGGER_ERROR(GFM_STRING("All the Shaders Attached to a Pipeline must be compiled first!"));
			}
			if(hasFragment && hasVertex) {
				break;
			}
		}
	}
	if(!hasFragment) {
		GFM_LOGGER_ERROR(GFM_STRING("A Pipeline needs a FragmentShader !"));
	}
	if(!hasVertex) {
		GFM_LOGGER_ERROR(GFM_STRING("A pipeline needs a VertexShader!"));
	}
}

void gfm::INTERNAL::gpu::GL::GLPipeline::CreateProgram() {
	m_id = glCreateProgram();
	for(auto i = 0U; i < static_cast<utils::uint32>(ShaderIndex::eSHADER_INDEX_MAXNUM); ++i) {
		if(m_AttachedShader[i] != nullptr) {
			ASSERT_GL(glAttachShader(m_id, dynamic_cast<const GLShader*>(m_AttachedShader[i])->GetID()));
		}
	}
}

void gfm::INTERNAL::gpu::GL::GLPipeline::CheckLinkingSuccessfull() {
	utils::int32 result = 0;
	utils::int32 length;
	ASSERT_GL(glGetProgramiv(m_id, GL_LINK_STATUS, &result));
	ASSERT_GL(glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length));
	if(length != 0) {
		char * errorMessage = reinterpret_cast<char *>(alloca(length * sizeof(char)));
		ASSERT_GL(glGetProgramInfoLog(m_id, length, &length, errorMessage));
		GFM_LOGGER_INFORMATION("Message from Linking the Program : ", errorMessage);
	}
	if(result == GL_FALSE) {
		GFM_LOGGER_ERROR("ERROR ON LINKING THE SHADER PROGRAM!");
		ASSERT_GL(glDeleteProgram(m_id));
		return;
	}
}

//TODO PASS ARRAY COUNT WITH IN AND USE IT IN THE DEFAULT CASE
//TODO PASS NORMALIZED IN FOR INT VALUES ETC
void gfm::INTERNAL::gpu::GL::GLPipeline::AppendVertexAttributes(
	utils::uint32 locationIndex, utils::uint32& attrOffset, String&& dataType) {
	auto vectorLambda = [this, &attrOffset](utils::uint32 index, utils::uint32  location){
		m_vertexAttributes.Append(VertexAttribute{m_type, VertexAttributeType::eFLOAT, location, attrOffset, index - 3, false});
		attrOffset += VertexAttribute::VertexAttributeTypeToSize(static_cast<VertexAttributeType>(index));
		m_vertexAttributeStride += VertexAttribute::VertexAttributeTypeToSize(static_cast<VertexAttributeType>(index));
	};
	for(auto index = 0U; index < traits::ArrayLen(Shader::GLSLAllowedVertexAttributeTypes); ++index) {
		if(dataType.StartsWith(Shader::GLSLAllowedVertexAttributeTypes[index])) {
			GFM_DEBUG_ASSERT(index >= static_cast<utils::uint32>(VertexAttributeType::eSTART_NUM) && index - 1 < static_cast<utils::uint32>(VertexAttributeType::eMAX_NUM),
				GFM_STRING("VertexAttributeType Index out of Range!"));
			GFM_DEBUG_ASSERT(!dataType.Contains(GFM_STRING('[')), GFM_STRING("Arrays currently not supported for VertexAttributes!"));
			switch(static_cast<VertexAttributeType>(index)) {
			case VertexAttributeType::eMAT2:
			case VertexAttributeType::eMAT3:
			case VertexAttributeType::eMAT4:
				for(auto i = locationIndex; i < locationIndex + (index - 6); ++i) {
					vectorLambda(index - 3, i);
				}
				break;
			case VertexAttributeType::eVEC2:
			case VertexAttributeType::eVEC3:
			case VertexAttributeType::eVEC4:
				vectorLambda(index, locationIndex);
				break;
			default:
				m_vertexAttributes.Append(VertexAttribute{m_type, static_cast<VertexAttributeType>(index), locationIndex, attrOffset, 1, false});
				attrOffset += VertexAttribute::VertexAttributeTypeToSize(static_cast<VertexAttributeType>(index));
				m_vertexAttributeStride += VertexAttribute::VertexAttributeTypeToSize(static_cast<VertexAttributeType>(index));
				break;
			}
			break;
		}
	}
}

void gfm::INTERNAL::gpu::GL::GLPipeline::ParseVertexAttributes() {
	const auto index = ShaderSource::VertexShaderIndex[static_cast<utils::uint32>(m_type)];
	const auto& sourceCode = m_AttachedShader[static_cast<utils::uint32>(ShaderTypeToIndex(ShaderType::eVERTEX))]->GetSourceCode();
	static const String LOCATIONTOKEN = GFM_STRING("layout(location=");
	static const String ATTRIBUTEINTOKEN = GFM_STRING(")in");
	thread_local static String numberString;
	auto trimedVertexSource = sourceCode.Trim();
	auto stringStartDigitLocation = 0;
	auto nextEndIndex = 0;
	auto attrOffset = 0U;
	auto dataType = ""_gs;
	for(auto i = 0U; i < trimedVertexSource.Length(); ++i) {
		stringStartDigitLocation = trimedVertexSource.IndexOf(i, LOCATIONTOKEN);
		if(stringStartDigitLocation != -1) {
			i = stringStartDigitLocation + LOCATIONTOKEN.Length() - 1;
			numberString.Clear();
			while(detail::CStringHelper::IsDigit(trimedVertexSource[++i])) {
				numberString.Append(trimedVertexSource[i]);
			}
			if(trimedVertexSource.SubString(i, ATTRIBUTEINTOKEN.Length()) != ATTRIBUTEINTOKEN) {
				i += ATTRIBUTEINTOKEN.Length();
				continue;
			}
			i += ATTRIBUTEINTOKEN.Length();
			GFM_DEBUG_ASSERT(numberString.IsNumber(), GFM_STRING("NumberString from VertexShader wasnt a Number!"))
			nextEndIndex = trimedVertexSource.IndexOf(i, GFM_STRING(';'));
			GFM_DEBUG_ASSERT(nextEndIndex != -1, GFM_STRING("Something went wrong on Parsing the Shader Attributes!"));
			AppendVertexAttributes(numberString.ToUInt(), attrOffset, trimedVertexSource.SubString(i, nextEndIndex - i));
		}
	}
}

void gfm::INTERNAL::gpu::GL::GLPipeline::DeleteAttachedShaders() noexcept {
	const GLShader* shader = nullptr;
	for(auto i = 0U; i < static_cast<utils::uint32>(ShaderIndex::eSHADER_INDEX_MAXNUM); ++i) {
		if(m_AttachedShader[i] != nullptr) {
			shader = dynamic_cast<const GLShader*>(m_AttachedShader[i]);
			ASSERT_GL(glDetachShader(m_id, shader->GetID()));
			shader->Destroy();
		}
	}
}

void gfm::INTERNAL::gpu::GL::GLPipeline::BindUniformBuffer(const UniformBuffer& ubo, const char* shaderBlockName) const {
	auto blockIndex = glGetUniformBlockIndex(m_id, shaderBlockName);
	//TODO CASH THE BLOCK INDICES !! WHEN DICT IS FINISH
	const GLUniformBuffer* glubo = dynamic_cast<const GLUniformBuffer*>(&ubo);
	glBindBufferBase(static_cast<utils::uint32>(BufferType::eUNIFORM), glubo->GetBindingPoint(), glubo->m_id);
	glUniformBlockBinding(m_id, blockIndex, glubo->GetBindingPoint());
}

bool gfm::INTERNAL::gpu::GL::GLPipeline::ValidateUniformBuffer(const UniformBuffer& ubo) const {
	return true; // TODO IMPLEMENT THIS METHOD
}
