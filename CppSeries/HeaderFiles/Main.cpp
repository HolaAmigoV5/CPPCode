#include <iostream>
#include "Common.h"
#include "Log.h"


int main() {
	int a = 8;
	a++;

	const char* string = "abcdef";
	for (int i = 0; i < 6; i++)
	{
		const char c = string[i];
		std::cout << c << std::endl;
		//Log(c);
	}

	InitLog();
	Log("Hello world!");

	std::cin.get();
}