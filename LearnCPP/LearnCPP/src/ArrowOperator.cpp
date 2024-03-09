// 重载箭头操作符
// 使用箭头运算符来获取内存中某个值的偏移量

#include <iostream>

class ArrowEntity
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
	ScopedPtr(ArrowEntity* entity)
		:m_Obj(entity) {
	}

	~ScopedPtr() {
		delete m_Obj;
	}

	// 重载操作符->
	ArrowEntity* operator->() {
		return m_Obj;
	}

	// 重载操作符
	const ArrowEntity* operator->() const {
		return m_Obj;
	}

private:
	ArrowEntity* m_Obj;
};

struct Vector3
{
	float x, y, z;
};

void ArrowEntityDemo() {
	// 指针函数调用
	ScopedPtr entity = new ArrowEntity();
	entity->Print();

	// 获取内存偏移量
	// &((Vector3*)nullptr)->z 然后强制转换为int
	float* offset = (float*)&((Vector3*)nullptr)->z;		//获取z的内存地址，为8
	std::cout << offset << std::endl;  // x,y,z地址依次为0,4,8
}