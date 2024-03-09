#pragma once

namespace Common {
	enum Level
	{
		LevelError = 0, LevelWarning, Levelinfo
	};

	class Log {
	private:
		Level m_LogLevel;
	public:
		Log()
		{
			m_LogLevel = Levelinfo;
		}

		~Log()
		{
		}

	public:
		void SetLevel(Level level);
		void Warn(const char* message) const;
		void Error(const char* message) const;
		void Info(const char* message) const;
	};
}
