#pragma once
#include "GL.h"
#include "GLShader.h"
#include "../../Utils/File/ReadAllLines.h"
#include "../../Utils/Logger.h"
#include "../../Macro/Assertions.h"

gfm::INTERNAL::gpu::GL::GLShader::GLShader(ShaderType type):
	Shader(type) {
	m_id = glCreateShader(static_cast<utils::int32>(m_type));
}

gfm::INTERNAL::gpu::GL::GLShader::GLShader(GLShader&& other) :
	Shader(other.m_type), m_id(other.m_id), m_isCompiled(true) {
	other.m_id = 0;
	other.m_isCompiled = false;
}
gfm::INTERNAL::gpu::GL::GLShader& gfm::INTERNAL::gpu::GL::GLShader::operator =(GLShader&& other) {
	if(this != &other) {
		m_id = other.m_id;
		m_type = other.m_type;
		m_isCompiled = true;
		other.m_id = 0;
		other.m_isCompiled = false;
	}
	return *this;
}

gfm::INTERNAL::gpu::GL::GLShader::~GLShader() noexcept {
	Destroy();
}

gfm::utils::uint32 gfm::INTERNAL::gpu::GL::GLShader::GetID() const noexcept {
	return m_id;
}

void gfm::INTERNAL::gpu::GL::GLShader::CreateFromFile(const String& filePath) {
	m_sourceCode = utils::file::ReadAllLines(filePath);
	if(m_sourceCode.Empty()) {
		GFM_LOGGER_ERROR(GFM_STRING("Unable to Open Shader File: {0}"), filePath);
		return;
	}
#if GFM_PLATFORM_WINDOWS
	char* shaderSourceBuffer = reinterpret_cast<char*>(alloca(m_sourceCode.Capacity()));
	detail::CStringHelper::Convert(m_sourceCode.CStr(), shaderSourceBuffer, m_sourceCode.Capacity());
	shaderSourceBuffer[m_sourceCode.Length()] = 0;
#else
	char* shaderSourceBuffer = m_sourceCode.CStr();
#endif
	auto len = static_cast<utils::int32>(m_sourceCode.Capacity());
	ASSERT_GL(glShaderSource(m_id, 1, &shaderSourceBuffer, &len));
	ASSERT_GL(glCompileShader(m_id));
	CheckCompileSuccessfull();
	m_isCompiled = true;
}

void gfm::INTERNAL::gpu::GL::GLShader::CreateFromSource(const String& source) {
	if(source.Empty()) {
		GFM_LOGGER_ERROR(GFM_STRING("Shader Source cant be an Empty String!"));
		return;
	}
	m_sourceCode = source;
	CreateFromSource();
}

void gfm::INTERNAL::gpu::GL::GLShader::CreateFromSource(String && source) {
	if(source.Empty()) {
		GFM_LOGGER_ERROR(GFM_STRING("Shader Source cant be an Empty String!"));
		return;
	}
	m_sourceCode = std::move(source);
	CreateFromSource();
}

void gfm::INTERNAL::gpu::GL::GLShader::CreateFromSource() {
#ifdef GFM_PLATFORM_WINDOWS
	char* shaderSourceBuffer = reinterpret_cast<char*>(alloca(m_sourceCode.Capacity() * sizeof(String::CharType)));
	detail::CStringHelper::Convert(m_sourceCode.CStr(), shaderSourceBuffer, m_sourceCode.Length());
	shaderSourceBuffer[m_sourceCode.Length()] = 0;
#else
	const char* shaderSourceBuffer = m_sourceCode.CStr();
#endif
	auto len = static_cast<utils::int32>(m_sourceCode.Capacity());
	ASSERT_GL(glShaderSource(m_id, 1, &shaderSourceBuffer, &len));
	ASSERT_GL(glCompileShader(m_id));
	CheckCompileSuccessfull();
	m_isCompiled = true;
}

void gfm::INTERNAL::gpu::GL::GLShader::Destroy() const noexcept {
	if(m_id == 0) {
		return;
	}
	ASSERT_GL(glDeleteShader(m_id));
	m_id = 0;
}

void gfm::INTERNAL::gpu::GL::GLShader::CheckCompileSuccessfull() {
	utils::int32 result;
	utils::int32 length;
	ASSERT_GL(glGetShaderiv(m_id, GL_COMPILE_STATUS, &result));
	ASSERT_GL(glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &length));
	if(length != 0) {
		char * errorMessage = reinterpret_cast<char*>(alloca(length * sizeof(char)));
		ASSERT_GL(glGetShaderInfoLog(m_id, length, &length, errorMessage));
		GFM_LOGGER_INFORMATION(GFM_STRING("Shader Compilition : {0}"), errorMessage);
	}
	if(result == GL_FALSE) {
		GFM_LOGGER_ERROR("Unable TO Compile Shader!");
		Destroy();
		return;
	}
}

bool gfm::INTERNAL::gpu::GL::GLShader::IsCompiled() const noexcept {
	return m_isCompiled;
}

const gfm::String& gfm::INTERNAL::gpu::GL::GLShader::GetSourceCode() const noexcept {
	GFM_DEBUG_ASSERT(!m_sourceCode.Empty(), GFM_STRING("Source Code is Empty!"));
	return m_sourceCode;
}

