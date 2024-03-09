// 重载箭头操作符
#include <iostream>

class Entity
{
public:
	int x;
	void Print() const {
		std::cout << "Hello!" << std::endl;
	}
};

class ScopedPtr
{
public:
	ScopedPtr(Entity* entity) :m_Obj(entity) {
	}
	~ScopedPtr() {
		delete m_Obj;
	}

	// 重载操作符->
	Entity* operator->() {
		return m_Obj;
	}

	// 重载操作符
	const Entity* operator->() const{
		return m_Obj;
	}

private:
	Entity* m_Obj;
};


//int main()
//{
//	ScopedPtr entity = new Entity();
//	entity->Print();
//
//    std::cin.get();
//}
