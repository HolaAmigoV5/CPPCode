#include <iostream>

void Variables() {
	int variable = 8;
	std::cout << variable << std::endl;

	float a = 2.3f;
	double b = 4.5;
	bool v = true;
	std::cout << "true: " << v << std::endl;	//true:1, false:0

	std::cout << "=================================" << std::endl;
	std::cout << "char�ֽ�����"<<sizeof(char) << std::endl;				// 1
	std::cout << "short�ֽ�����" << sizeof(short) << std::endl;			// 2
	std::cout << "long�ֽ�����" << sizeof(long) << std::endl;			// 4
	std::cout << "double�ֽ�����" << sizeof(double) << std::endl;		// 8
	std::cout << "long long�ֽ�����" << sizeof(long long) << std::endl;	// 8
	std::cout << "bool�ֽ�����" << sizeof(bool) << std::endl;			//1
}