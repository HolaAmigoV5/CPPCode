// 智能指针，用于自动回收堆上创建的对象，无需手动delete。
// unique_ptr 是作用域指针，超出作用域时，它会被销毁，不能复制
// shared_ptr 共享指针，通过引用计数跟踪指针有多少引用，当计数为0时，就被delete
// weak_ptr 不会增加引用计数

#include <iostream>
#include <memory>

class Entity
{
public:
	Entity();
	~Entity();

	void Print() {
		std::cout << "Hello world!" << std::endl;
	}
private:

};

Entity::Entity()
{
	std::cout << "Created Entity!" << std::endl;
}

Entity::~Entity()
{
	std::cout << "Destroyed Entity!" << std::endl;
}

//Entity::Print() {
//	std::cout << "Hello world!" << std::endl;
//}

int main()
{
	{
		std::shared_ptr<Entity> e1;
		std::weak_ptr<Entity> weakEntity;
		{
			//std::unique_ptr<Entity> entity = new Entity(); // 错误，unique_ptr是显示转换

			//std::unique_ptr<Entity> entity(new Entity());
			// 推荐写法，若构造函数碰巧抛出异常，会安全些。make_unique是在c++ 14中引入，c++ 11不支持
			std::unique_ptr<Entity> entity = std::make_unique<Entity>();
			//std::unique_ptr<Entity> e0 = entity;  // 拷贝构造函数和拷贝构造操作符，实际被删除了
			entity->Print();

			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();	// 共享指针
			e1 = sharedEntity;

			weakEntity = sharedEntity; // 这里不会增加引用计数，作用域外会被销毁
		}
	}

	std::cin.get();
}