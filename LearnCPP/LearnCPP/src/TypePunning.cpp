#include <iostream>

struct Entity
{
	int x, y;
};

void TypePunningDemo() {
	//int a = 50;
	//double& value = *((double*)&a);	// 类型双关。把int类型转换成double
	//std::cout << value << std::endl;

	Entity e = { 5,8 };
	int* position = (int*)&e;	// 结构转换成数组
	std::cout << position[0] << ", " << position[1] << std::endl;
}