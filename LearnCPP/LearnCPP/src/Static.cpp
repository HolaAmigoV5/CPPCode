#include <iostream>

struct Entity
{
	static int x, y;	//����������Entity�������ʵ����ֻ��һ��ʵ��
	static void Print() {
		std::cout << x << ", " << y << std::endl;
	}
};

// ����Ҫ���������������������Ҳ�����������
int Entity::x;	// ����ΪEntity�������ռ��д�������x
int Entity::y;	// ����ΪEntity�������ռ��д�������y

void CallStaticDemo() {
	Entity e;
	e.x = 2;
	e.y = 3;

	Entity e1;
	e1.x = 4;
	e1.y = 5;

	e.Print();		// ���4, 5
	e1.Print();		// ���4��5
}