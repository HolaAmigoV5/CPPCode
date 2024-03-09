#include <iostream>
#include <memory>


// 智能指针，用于自动回收堆上创建的对象，无需手动delete。
// unique_ptr 是作用域指针，超出作用域时，它会被销毁，不能复制
// shared_ptr 共享指针，通过引用计数跟踪指针有多少引用，当计数为0时，就被delete
// weak_ptr 不会增加引用计数


class SmartEntity
{
public:
	SmartEntity()
	{
		std::cout << "Created Entity!" << std::endl;
	}

	~SmartEntity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print() {
		std::cout << "Print SmartEntity" << std::endl;
	}
};

void SmartPointerDemo() {
	std::shared_ptr<SmartEntity> e1;
	std::weak_ptr<SmartEntity> weakEntity;

	{
		//std::unique_ptr<SmartEntity> entity = new SmartEntity(); //错误，unique_ptr是显示转换
		//std::unique_ptr<SmartEntity> entity(new SmartEntity());
		
		// make_unique是c++14中引入，11不支持。
		// 若构造函数碰巧抛出异常，会安全些。推荐写法。
		std::unique_ptr<SmartEntity> entity = std::make_unique<SmartEntity>();

		// 拷贝构造函数和拷贝构造操作符，实际被删除了
		//std::unique_ptr<SmartEntity> e0 = entity;  // 编译错误

		entity->Print();

		// 共享指针，可以复制
		std::shared_ptr<SmartEntity> sharedEntity = std::make_shared<SmartEntity>();
		e1 = sharedEntity;

		weakEntity = sharedEntity; // 这里不会增加引用计数，作用域外会被销毁
	}
}
