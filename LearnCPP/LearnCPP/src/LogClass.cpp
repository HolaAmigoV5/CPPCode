#include "LogClass.h"
#include <iostream>

void LogClass::SetLevel(Level level) {
	m_LogLevel = level;
}

void LogClass::Warn(const char* message) const {
	if (m_LogLevel >= LevelWarning)
		std::cout << "[WARNING]:" << message << std::endl;
}

void LogClass::Error(const char* message) const {
	if (m_LogLevel >= LevelError)
		std::cout << "[ERROR]:" << message << std::endl;
}

void LogClass::Info(const char* message) const {
	if (m_LogLevel >= Levelinfo)
		std::cout << "[INFO]:" << message << std::endl;
}

