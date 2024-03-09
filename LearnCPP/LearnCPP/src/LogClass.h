#pragma once
enum Level
{
	LevelError = 0, LevelWarning, Levelinfo
};


///****************************************************************************          
/// @brief   : 类的声明和实现进行分开。这里进行类的声明
/// @author  : Wby
/// @date    :                                                     
///****************************************************************************

class LogClass {
private:
	Level m_LogLevel = Levelinfo;
public:
	LogClass()
	{
	}

	~LogClass()
	{
	}

public:
	void SetLevel(Level level);
	void Warn(const char* message) const;
	void Error(const char* message) const;
	void Info(const char* message) const;
};

