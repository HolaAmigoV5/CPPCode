// ʹ�ü�ͷ���������ȡ�ڴ���ĳ��ֵ��ƫ����
#include <iostream>

struct Vector3
{
	float x, y, z;
};

int main() {
	// &((Vector3*)nullptr)->z Ȼ��ǿ��ת��Ϊint
	int offset = (int)&((Vector3*)nullptr)->z;		//��ȡz���ڴ��ַ��Ϊ8
	std::cout << offset << std::endl;  // x,y,z��ַ����Ϊ0,4,8

	std::cin.get();
}