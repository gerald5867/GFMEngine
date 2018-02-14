template<typename... ArgTypes>
void gfm::utils::Logger::Error(const String& format, const String::CharType* func, const String::CharType* file, const String::CharType* line, ArgTypes&&... arguments) const {
	std::lock_guard<std::mutex> locker(m_logMutex);
	m_logDate.UpdateNow();
	m_logBuffer.Clear();
	utils::ChangeCoutColor(utils::ConsoleColor::eRED);
	String::FormatBuffer(GFM_STRING("{0} ERROR( File:{1} Function:{2} Line:{3} ): \n"), m_logBuffer, m_logDate.GetDate(), file, func, line);
	m_logBuffer += String::Format(format.CStr(), std::forward<ArgTypes&&>(arguments)...);
	WriteBuffer();
	utils::ChangeCoutColor(utils::ConsoleColor::eDEFAULT);
}

template<typename... ArgTypes>
void gfm::utils::Logger::FatalError(const String& format, const String::CharType* func, const String::CharType* file, const String::CharType* line, ArgTypes&&... arguments) const {
	std::lock_guard<std::mutex> locker(m_logMutex);
	m_logDate.UpdateNow();
	m_logBuffer.Clear();
	utils::ChangeCoutColor(utils::ConsoleColor::eRED);
	String::FormatBuffer(GFM_STRING("{0} FATAL ERROR !!!! ( File:{1} Function:{2} Line:{3} ): \n"), m_logBuffer, m_logDate.GetDate(), file, func, line);
	m_logBuffer += String::Format(format.CStr(), std::forward<ArgTypes&&>(arguments)...);
	WriteBuffer();
	utils::ChangeCoutColor(utils::ConsoleColor::eDEFAULT);
}

template<typename... ArgTypes>
void gfm::utils::Logger::Log(const String& format, const String::CharType* func, const String::CharType* file, const String::CharType* line, ArgTypes&&... arguments) const {
	std::lock_guard<std::mutex> locker(m_logMutex);
	m_logDate.UpdateNow();
	m_logBuffer.Clear();
	m_logBuffer += String::Format(format.CStr(), std::forward<ArgTypes&&>(arguments)...);
	WriteBuffer();
}
template<typename... ArgTypes>
void gfm::utils::Logger::Information(const String& format, ArgTypes&&... arguments) const {
	std::lock_guard<std::mutex> locker(m_logMutex);
	m_logBuffer.Clear();
	utils::ChangeCoutColor(utils::ConsoleColor::eGREEN);
	m_logBuffer.Append(GFM_STRING("INFORMATION: \n"));
	m_logBuffer += String::Format(format.CStr(), std::forward<ArgTypes&&>(arguments)...);
	WriteBuffer();
	utils::ChangeCoutColor(utils::ConsoleColor::eDEFAULT);
}
template<typename... ArgTypes>
void gfm::utils::Logger::Warning(const String& format, const String::CharType* func, const String::CharType* file, const String::CharType* line, ArgTypes&&... arguments) const {
	std::lock_guard<std::mutex> locker(m_logMutex);
	m_logDate.UpdateNow();
	m_logBuffer.Clear();
	utils::ChangeCoutColor(utils::ConsoleColor::eYELLOW);
	String::FormatBuffer(GFM_STRING("{0} WARNING( File:{1} Function:{2} Line:{3} ): \n"), m_logBuffer, m_logDate.GetDate(), file, func, line);
	m_logBuffer += String::Format(format.CStr(), std::forward<ArgTypes&&>(arguments)...);
	WriteBuffer();
	utils::ChangeCoutColor(utils::ConsoleColor::eDEFAULT);
}