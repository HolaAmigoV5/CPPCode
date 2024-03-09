#include <iostream>

// 参数的调用顺序不定

void PrintSum(int a, int b) {
	std::cout << a << " + " << b << " = " << (a + b) << std::endl;
}

void ArgumentEvOrder() {
	int value = 0;
	PrintSum(value++, value++);		// 输出 1+0=1;
}