#include <iostream>

// �����ĵ���˳�򲻶�

void PrintSum(int a, int b) {
	std::cout << a << " + " << b << " = " << (a + b) << std::endl;
}

void ArgumentEvOrder() {
	int value = 0;
	PrintSum(value++, value++);		// ��� 1+0=1;
}