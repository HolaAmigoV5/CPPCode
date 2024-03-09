#include <iostream>

class Entity
{
public:
	float X, Y;
	Entity();		// 默认构造函数
	Entity(float x, float y) {
		// 重载，带参数的构造函数
		X = x;
		Y = y;
	}
	~Entity();		// 析构函数

	void Print() {
		std::cout << X << ", " << Y << std::endl;
	}

private:

};

Entity::Entity()
{
	X = 0.0f; Y = 0.0f;
	std::cout << "Created Entity!" << std::endl;
}

Entity::~Entity()
{
	std::cout << "Destroyed Entity!" << std::endl;
}

//int main() {
//	Entity e;
//	e.Print();
//
//	std::cout << "================================" << std::endl;
//
//	//Entity e1(5, 6);
//	//e1.Print();
//}