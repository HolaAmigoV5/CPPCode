#include <iostream>

void Variables() {
	int variable = 8;
	std::cout << variable << std::endl;

	float a = 2.3f;
	double b = 4.5;
	bool v = true;
	std::cout << "true: " << v << std::endl;	//true:1, false:0

	std::cout << "=================================" << std::endl;
	std::cout << "char字节数："<<sizeof(char) << std::endl;				// 1
	std::cout << "short字节数：" << sizeof(short) << std::endl;			// 2
	std::cout << "long字节数：" << sizeof(long) << std::endl;			// 4
	std::cout << "double字节数：" << sizeof(double) << std::endl;		// 8
	std::cout << "long long字节数：" << sizeof(long long) << std::endl;	// 8
	std::cout << "bool字节数：" << sizeof(bool) << std::endl;			//1
}