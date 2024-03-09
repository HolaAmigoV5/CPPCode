// 使用箭头运算符来获取内存中某个值的偏移量
#include <iostream>

struct Vector3
{
	float x, y, z;
};

int main() {
	// &((Vector3*)nullptr)->z 然后强制转换为int
	int offset = (int)&((Vector3*)nullptr)->z;		//获取z的内存地址，为8
	std::cout << offset << std::endl;  // x,y,z地址依次为0,4,8

	std::cin.get();
}