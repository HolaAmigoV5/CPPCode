#include <iostream>

struct Entity
{
	static int x, y;	//两个变量在Entity类的所有实例中只有一个实例
	static void Print() {
		std::cout << x << ", " << y << std::endl;
	}
};

// 这里要声明变量，否则链接器找不到两个变量
int Entity::x;	// 在名为Entity的命名空间中创建变量x
int Entity::y;	// 在名为Entity的命名空间中创建变量y

void CallStaticDemo() {
	Entity e;
	e.x = 2;
	e.y = 3;

	Entity e1;
	e1.x = 4;
	e1.y = 5;

	e.Print();		// 输出4, 5
	e1.Print();		// 输出4，5
}