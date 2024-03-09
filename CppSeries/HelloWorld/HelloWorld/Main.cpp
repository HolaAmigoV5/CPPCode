#include <iostream>

void Log(const char* message);

int main() {
	//std::cout << "Hello World!" << std::endl;
	Log("Hello World!");

	int variable = 8;
	std::cout << variable << std::endl;

	variable = 20;
	std::cout << variable << std::endl;

	float a = 2.3f;
	double b = 4.5;
	bool v = true;
	std::cout << v << std::endl;

	std::cout << "=================================" << std::endl;
	std::cout <<sizeof(char) << std::endl;
	std::cout << sizeof(short) << std::endl;
	std::cout << sizeof(long) << std::endl;
	std::cout << sizeof(double) << std::endl;
	std::cout << sizeof(long long) << std::endl;
	std::cout << sizeof(bool) << std::endl;

	std::cin.get();
}