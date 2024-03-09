#pragma once
enum Level
{
	LevelError = 0, LevelWarning, Levelinfo
};


///****************************************************************************          
/// @brief   : ���������ʵ�ֽ��зֿ�����������������
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

