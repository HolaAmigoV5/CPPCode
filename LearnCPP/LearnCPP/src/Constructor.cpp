// ���캯�����������ͷ�����һ��ÿ�ι���һ������ʱ������õķ�����
// c++����Ҫ�ֶ���ʼ������ֵ������java��C#

#include <iostream>

class Entity
{
public:
	float X, Y;
	// ���캯����Ҫ������ʼ������
	Entity() {
		X = 0.0f;
		Y = 0.0f;

		std::cout << "Created Entity!" << std::endl;
	};
	//Entity() =delete;	// Ĭ�Ϲ��캯������������ɾ��

	// ���캯������
	Entity(float x, float y) {
		X = x;
		Y = y;
	}

	// ��������
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
