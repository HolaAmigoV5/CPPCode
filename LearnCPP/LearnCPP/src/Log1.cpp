#include <iostream>

// 定义Log()方法的实现
// LNK1169: 找到一个或多个多重定义的符号。添加static或inline关键字可以解决
void Log(const char* message) {
	std::cout << message << std::endl;
}