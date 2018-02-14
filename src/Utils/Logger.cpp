#pragma once
#include <GL/glew.h>
#include "../Macro/Assertions.h"
#include <iostream>
#include "Logger.h"

gfm::utils::Logger* gfm::policy::MakeSingletonPtr<gfm::utils::Logger>::mp_instance = nullptr;

void gfm::utils::Logger::Initialize(const String & logFilePath, LogOutput outputResourceBits) {
	if (mp_instance != nullptr) {
		return;
	}
	mp_instance = new Logger();
	mp_instance->m_outputResources = outputResourceBits;
	mp_instance->m_logFileStream.Open(logFilePath.CStr(), file::FileOpenMode::eTEXT_APPEND_UPDATE);
	GFM_DEBUG_ASSERT(mp_instance->m_logFileStream.IsOpen(), GFM_STRING("Log File failed to Open!"));
}

void gfm::utils::Logger::Destroy() noexcept {
	mp_instance->m_logFileStream.Close();
	if (mp_instance != nullptr) {
		delete mp_instance;
		mp_instance = nullptr;
	}
}

void gfm::utils::Logger::ClearGLError() {
	utils::uint32 watchdog = 255;
	while (glGetError() != GL_NO_ERROR && --watchdog){
	}
}

void gfm::utils::Logger::Flush() const {
	m_logFileStream.Write(m_logBuffer.CStr(), sizeof(String::CharType), m_logBuffer.Length());
	m_logFileStream.Close();
	m_logFileStream.Open("LogFile.txt", file::FileOpenMode::eTEXT_APPEND_UPDATE);
}

bool gfm::utils::Logger::LogGLCall(const String::CharType * func, const String::CharType * file, const String::CharType* line) {
	std::lock_guard<std::mutex> locker(m_logMutex);
	bool noError = true;
	while (int errorCode = glGetError()) {
		m_glErrorMessages.Append(errorCode);
		noError = false;
	}
	if (!noError) {
		m_logBuffer.Clear();
		m_logBuffer += String::Format(L"OpenGL ERROR in function {0} at File {1}, on Line {2} \n", func, file, line);
		for (int errCode : m_glErrorMessages) {
			m_logBuffer += String::Format(L"\t OpenGL Error Code : {0}", errCode);
			//TODO make a function that converts the errCode to the enum string //
		}
		WriteBuffer();
	}
	return noError;
}

void gfm::utils::Logger::WriteBuffer() const
{
	if (static_cast<bool>(m_outputResources & LogOutput::eCOUT)) {
#if GFM_PLATFORM_WINDOWS
		std::wcout << m_logBuffer.CStr() << std::endl;
#else
		std::cout << m_logBuffer.CStr(); << std::endl;
#endif // WIN
	}
	if (static_cast<bool>(m_outputResources & LogOutput::eFILE)) {
		Flush();
	}
}

void gfm::utils::Logger::AssertionFailure(const String::CharType* func, const String::CharType* file, const String::CharType* line,
	const String& assertionMessage, const String::CharType* condition) const {
	thread_local static constexpr const String::CharType* const ASSERTION_POSTFIX = GFM_STRING(
		"*******************************************************************\n"
		 "*******************************************************************\n"
		 "                          ASSERTION FAILED!!!                      \n"
		 "*******************************************************************\n"
		 "*******************************************************************\n"
	);
	thread_local static constexpr const String::CharType* const ASSERTION_FORMAT = GFM_STRING(
			"***  FILE:           {0}\n"
			"***  FUNCTION:       {1}\n"
			"***  LINE:           {2}\n"
			"***  CONDITION:      {3}\n"
			"***  ASSERTION TEXT: {4}\n"
			"*******************************************************************\n"
	);
	std::lock_guard<std::mutex> locker(m_logMutex);
	m_logBuffer.Clear();
	m_logBuffer += ASSERTION_POSTFIX;
	String::FormatBuffer(ASSERTION_FORMAT, m_logBuffer, file::GetFileFromPath(file), func, line, condition, assertionMessage);
	utils::ChangeCoutColor(utils::ConsoleColor::eLIGHT_RED);
	WriteBuffer();
	utils::ChangeCoutColor(utils::ConsoleColor::eDEFAULT);
}
