
#include <iostream>

class Player
{
public:
	int x, y;
	int speed;
	void Move(int xa, int ya) {
		x += xa * speed;
		y += ya * speed;
	}

private:

};

class Log
{
public:
	/*const int LogLevelError = 0;
	const int LogLevelWarning = 1;
	const int LogLevelInfo = 2;*/
	enum Level
	{
		LevelError = 0, LevelWarning, Levelinfo
	};

public:
	void SetLevel(Level level) {
		m_LogLevel = level;
	}

	void Warn(const char* message) {
		if (m_LogLevel >= LevelWarning)
			std::cout << "[WARNING]:" << message << std::endl;
	}

	void Error(const char* message) {
		if (m_LogLevel >= LevelError)
			std::cout << "[ERROR]:" << message << std::endl;
	}

	void Info(const char* message) {
		if (m_LogLevel >= Levelinfo)
			std::cout << "[INFO]:" << message << std::endl;
	}
	
private:
	Level m_LogLevel = Levelinfo;
};



//int main()
//{
//	//Player player;		// 声明一个类的实例player
//	//player.x = 5;
//	//player.Move(2, 3);
//
//	Log log;
//	log.SetLevel(Log::Levelinfo);
//	log.Warn("Hello!");
//	log.Error("Hello!");
//	log.Info("Hello!");
//
//
//	std::cin.get();
//}
