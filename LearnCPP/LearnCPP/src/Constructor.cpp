// 构造函数是特殊类型方法，一种每次构造一个对象时都会调用的方法。
// c++中需要手动初始化变量值，不像java或C#

#include <iostream>

class Entity
{
public:
	float X, Y;
	// 构造函数主要用来初始化对象
	Entity() {
		X = 0.0f;
		Y = 0.0f;

		std::cout << "Created Entity!" << std::endl;
	};
	//Entity() =delete;	// 默认构造函数，可以这样删除

	// 构造函数重载
	Entity(float x, float y) {
		X = x;
		Y = y;
	}

	// 析构函数
	~Entity() {
		std::cout << "Destroyed Entity!" << std::endl;
	};	

	void Print() {
		std::cout << X << ", " << Y << std::endl;
	}
};

void CallConstructorDemo() {
	Entity e;
	e.Print();

	Entity e1(10.0f, 5.0f);
	e1.Print();
}
