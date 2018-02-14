#pragma once
#ifndef LOGGER_H
#define LOGGER_H
#include <ctime>
#include <mutex> //TODO MAKE EVERYTHING THREAD SAFE
#include "File/FileStream.h"
#include "../Macro/BestInline.h"
#include "../Macro/Assertions.h"
#include "Date.h"
#include "../Platform/ChangeCoutColor.h"
#include "File/GetFileFromPath.h"
#include "../Policys/Singleton.h"
#include "../DataStructures/List.h"
#include "../DataStructures/String.h"

//EIGENE METHODE FÜR ASSERTION!
//TOSTRING METHODEN FUER ALLE TYPEN

#define GFM_LOG_LEVEL_INFORMATION 4
#define GFM_LOG_LEVEL_WARNING 3
#define GFM_LOG_LEVEL_ERROR 2
#define GFM_LOG_LEVEL_FATAL_ERROR 1

#ifndef GFM_LOGGER_INFORMATION
#	if defined GFM_LOGGER_LEVEL && GFM_LOGGER_LEVEL >= GFM_LOG_LEVEL_INFORMATION || !defined GFM_LOGGER_LEVEL 
#		define GFM_LOGGER_INFORMATION(format, ...) \
			gfm::utils::Logger::instance().Information(format,  __VA_ARGS__); 
#	else
#			define GFM_LOGGER_INFORMATION(format, ...)
#	endif
#endif

#ifndef GFM_LOGGER_WARNING
#	if defined GFM_LOGGER_LEVEL && GFM_LOGGER_LEVEL >= GFM_LOG_LEVEL_WARNING || !defined GFM_LOGGER_LEVEL 
#		define GFM_LOGGER_WARNING(format, ...) \
			gfm::utils::Logger::instance().Warning(format, \
			gfm::String(__FUNCTION__).CStr(),  gfm::utils::file::GetFileFromPath(GFM_WSTRING(__FILE__)).CStr(), GFM_WSTRING(__LINE__), __VA_ARGS__);
#	else
#		define GFM_LOGGER_WARNING(format, ...)
#	endif
#endif

#ifndef GFM_LOGGER_ERROR
#	if defined GFM_LOGGER_LEVEL && GFM_LOGGER_LEVEL >= GFM_LOG_LEVEL_ERROR || !defined GFM_LOGGER_LEVEL 
#		define GFM_LOGGER_ERROR(format, ...) \
			gfm::utils::Logger::instance().Error(format, \
			gfm::String(__FUNCTION__).CStr(),  gfm::utils::file::GetFileFromPath(GFM_WSTRING(__FILE__)).CStr(), GFM_WSTRING(__LINE__), __VA_ARGS__); \
			GFM_DEBUG_BREAK;
#	else
#		define GFM_LOGGER_ERROR(format, ...)
#	endif
#endif

#ifndef GFM_LOGGER_FATAL_ERROR
#	if defined GFM_LOGGER_LEVEL && GFM_LOGGER_LEVEL >= GFM_LOG_LEVEL_FATAL_ERROR || !defined GFM_LOGGER_LEVEL 
#		define GFM_LOGGER_FATAL_ERROR(format, ...) \
			gfm::utils::Logger::instance().FatalError(format, \
			gfm::String(__FUNCTION__).CStr(),  gfm::utils::file::GetFileFromPath(GFM_WSTRING(__FILE__)).CStr(), GFM_WSTRING(__LINE__), __VA_ARGS__); \
			GFM_DEBUG_BREAK;
#	else
#		define GFM_LOGGER_FATAL_ERROR(format, ...)
#	endif
#endif



namespace gfm {
namespace utils {
	enum class LogOutput {
		eNO_OUTPUT = (0 << 0),
		eCOUT = (1 << 0),
		eFILE = (1 << 1)
	};
}//gfm
}//utils

GFM_BEST_INLINE constexpr gfm::utils::LogOutput operator | (gfm::utils::LogOutput left, gfm::utils::LogOutput right) noexcept {
	return static_cast<gfm::utils::LogOutput>(static_cast<int>(left) | static_cast<int>(right));
}

GFM_BEST_INLINE constexpr gfm::utils::LogOutput operator & (gfm::utils::LogOutput left, gfm::utils::LogOutput right) noexcept {
	return static_cast<gfm::utils::LogOutput>(static_cast<int>(left) & static_cast<int>(right));
}

namespace gfm {
namespace utils {
	class Logger final : public policy::MakeSingletonPtr<Logger>
	{
	public:
		static void Initialize(const String& logFilePath, LogOutput outputBits);
		static void Destroy() noexcept;
	public:
		void ClearGLError();
		void Flush() const;
		bool LogGLCall(const String::CharType * func, const String::CharType * file, const String::CharType* line);

		template<typename... ArgTypes>
		void Error(const String& format, const String::CharType* func, const String::CharType* file, const String::CharType* line, ArgTypes&&... arguments) const;

		template<typename... ArgTypes>
		void FatalError(const String& format, const String::CharType* func, const String::CharType* file, const String::CharType* line, ArgTypes&&... arguments) const;

		template<typename... ArgTypes>
		void Log(const String& format, const String::CharType* func, const String::CharType* file, const String::CharType* line, ArgTypes&&... arguments) const;

		template<typename... ArgTypes>
		void Information(const String& format, ArgTypes&&... arguments) const;

		template<typename... ArgTypes>
		void Warning(const String& format, const String::CharType* func, const String::CharType* file, const String::CharType* line, ArgTypes&&... arguments) const;

		void AssertionFailure(const String::CharType* func, const String::CharType* file, const String::CharType* line, 
			const String& assertionMessage, const String::CharType* condition) const;
	private:
		void WriteBuffer() const;
		Logger() = default;
	private:
		List<int32> m_glErrorMessages;
		mutable file::FileStream m_logFileStream;
		mutable String m_logBuffer;
		LogOutput m_outputResources;
		mutable std::mutex m_logMutex;
		mutable utils::Date m_logDate;
	};
}
}
#include "Logger.inl"

#endif //LOGGER_H



