
#include <iostream>
#include <string>

using String = std::string;

class Entity
{
public:
	Entity() :m_Name("Unknown") {}
	Entity(const String& name) :m_Name("Unknown") {}

	const String& GetName() const { return m_Name; }

private:
	String m_Name;
};



int main()
{
	// 创建实例方式一：栈上创建，适合小对象创建
	Entity entity("Wby");	// 栈上创建，使用默认构造函数创建entity对象实例。
	std::cout << entity.GetName() << std::endl;


	// 创建实例方式二：堆上创建，适合大对象创建
	Entity* e;
	{
		Entity* entity1 = new Entity("Wby");  // 堆上创建，必须手动释放
		e = entity1;
		std::cout << (*entity1).GetName() << std::endl;
		std::cout << entity1->GetName() << std::endl;	// 和上面代码一样
	}
	

	delete e;			// 释放e对象

	std::cin.get();
}

