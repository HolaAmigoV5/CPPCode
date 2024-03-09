#include <iostream>
#include "Log.h"

namespace Common {
	void Log::SetLevel(Level level) {
		m_LogLevel = level;
	}

	void Log::Warn(const char* message) const {
		if (m_LogLevel >= LevelWarning)
			std::cout << "[WARNING]:" << message << std::endl;
	}

	void Log::Error(const char* message) const {
		if (m_LogLevel >= LevelError)
			std::cout << "[ERROR]:" << message << std::endl;
	}

	void Log::Info(const char* message) const {
		if (m_LogLevel >= Levelinfo)
			std::cout << "[INFO]:" << message << std::endl;
	}
}