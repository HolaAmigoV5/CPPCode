#include <iostream>

struct Entity
{
	int x, y;
};

void TypePunningDemo() {
	//int a = 50;
	//double& value = *((double*)&a);	// ����˫�ء���int����ת����double
	//std::cout << value << std::endl;

	Entity e = { 5,8 };
	int* position = (int*)&e;	// �ṹת��������
	std::cout << position[0] << ", " << position[1] << std::endl;
}