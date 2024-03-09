
#include <iostream>

class Entity
{
public:
	Entity() {
		std::cout << "Created Entity!" << std::endl;
	};
	~Entity() {
		std::cout << "Destroyed Entity!" << std::endl;
	};

private:

};


// 作用域指针类
class ScopedPtr
{
public:
	ScopedPtr(Entity* ptr) :m_Ptr(ptr) {};
	~ScopedPtr() {
		delete m_Ptr;
	}

private:
	Entity* m_Ptr;
};

int main()
{
	{
		//Entity e;	// {} 作用域内"Created Entity"，作用域外"Destroyed Entity"
		//Entity* e1 = new Entity();	// 作用域内"Created Entity"，作用域外不销毁

		ScopedPtr sp(new Entity());	// 栈上创建，{}作用域外自动销毁Entity对象
	}

	std::cin.get();
}


