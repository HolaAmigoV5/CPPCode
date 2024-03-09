#include <iostream>

//int s_Variable = 10;
extern int s_Variable;	// extern关键字：在外部链接s_Variable变量，下面打印出5

struct  Entity
{
	static int x, y;
	void Print() {
		std::cout << x << "," << y << std::endl;
	}
};

int Entity::x;
int Entity::y;

//int main() {
//	std::cout << s_Variable << std::endl;
//	std::cout << "====================================" << std::endl;
//	
//	Entity e;
//	e.x = 2;	// 相当于：Entity::x=2;
//	e.y = 3;	// 相当于：Entity::y=3;
//
//	//Entity e1 = { 4,5 };
//	Entity e1;
//	e1.x = 4;		// Entity::x=4;
//	e1.y = 5;		// Entity::y=5;
//
//	e.Print();	// 相当于：Entity::Print();
//	e1.Print();
//
//	std::cin.get();
//}