#include "GL.h"
#include "GLErrorHandler.h"

bool gfm::INTERNAL::gpu::GL::GLErrorHandler::LogCall(const String::CharType* func, const String::CharType* file, const String::CharType* line) {
	bool noError = true;
	utils::uint32 watchdog = 255;
	while(int errorCode = glGetError() && --watchdog) {
		m_errorMessages.Append(errorCode);
		noError = false;
	}
	if(!noError) {
		m_lastError.Clear();
		m_lastError += String::Format(GFM_STRING("OpenGL ERROR in function {0} at File {1}, on Line {2} \n"), func, file, line);
		for(int errCode : m_errorMessages) {
			m_lastError += String::Format(GFM_STRING("\t OpenGL Error Code : {0} \n"), errCode);
			//TODO make a function that converts the errCode to the enum string //
		}
	}
	return noError;
}

void gfm::INTERNAL::gpu::GL::GLErrorHandler::ClearLastError() const {
	utils::uint32 watchdog = 255;
	while(glGetError() != GL_NO_ERROR && --watchdog) {
	}
}

const gfm::String& gfm::INTERNAL::gpu::GL::GLErrorHandler::GetLastError() const noexcept {
	return m_lastError;
}
