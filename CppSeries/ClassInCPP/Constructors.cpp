#include <iostream>

class Entity
{
public:
	float X, Y;
	Entity();		// Ĭ�Ϲ��캯��
	Entity(float x, float y) {
		// ���أ��������Ĺ��캯��
		X = x;
		Y = y;
	}
	~Entity();		// ��������

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