#include <iostream>

//int s_Variable = 10;
extern int s_Variable;	// extern�ؼ��֣����ⲿ����s_Variable�����������ӡ��5

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
//	e.x = 2;	// �൱�ڣ�Entity::x=2;
//	e.y = 3;	// �൱�ڣ�Entity::y=3;
//
//	//Entity e1 = { 4,5 };
//	Entity e1;
//	e1.x = 4;		// Entity::x=4;
//	e1.y = 5;		// Entity::y=5;
//
//	e.Print();	// �൱�ڣ�Entity::Print();
//	e1.Print();
//
//	std::cin.get();
//}